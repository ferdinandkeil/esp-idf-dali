#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <driver/rmt_tx.h>
#include <driver/rmt_rx.h>
#include "dali.h"

#define DALI_ADDRESS_TYPE_SHORT_MASK        0x00
#define DALI_ADDRESS_TYPE_GROUP_MASK        0x80
#define DALI_ADDRESS_TYPE_BROADCAST_MASK    0xfe
#define DALI_ADDRESS_TYPE_SPECIAL_CMD_MASK  0xa0

#define DALI_COMMAND_REPEAT_TIME_MS    40
#define DALI_BACKWARD_FRAME_TIMEOUT_MS 40 // (22 Te + 22 Te) * 417 us/Te = 18 ms

#define DALI_RESULT_NO_REPLY  -1

#define CHECK_ARG(ARG) do { if (!(ARG)) return ESP_ERR_INVALID_ARG; } while (0)
#define CHECK_FOR_ERROR(X) do { esp_err_t ___ = X; if (___ != ESP_OK) { return ___; }} while(0)
#define CHECK_POINTER(P) do { if (P == NULL) { return ESP_ERR_NOT_FOUND; }} while(0)

typedef enum {
    DALI_RECEIVE_PREV_BIT_ZERO,
    DALI_RECEIVE_PREV_BIT_ONE
} dali_receivePrevBit_t;

rmt_channel_handle_t dali_rxChannel;
rmt_receive_config_t dali_rxChannelConfig;
QueueHandle_t dali_rxChannelQueue;
rmt_channel_handle_t dali_txChannel;
rmt_tx_channel_config_t dali_txChannelConfig;
rmt_encoder_handle_t dali_txChannelEncoder;

static const rmt_symbol_word_t DALI_SYMBOL_ONE = {
    .level0 = 1,
    .duration0 = DALI_USTORMT(DALI_ONE_TE),
    .level1 = 0,
    .duration1 = DALI_USTORMT(DALI_ONE_TE),
};

static const rmt_symbol_word_t DALI_SYMBOL_ZERO = {
    .level0 = 0,
    .duration0 = DALI_USTORMT(DALI_ONE_TE),
    .level1 = 1,
    .duration1 = DALI_USTORMT(DALI_ONE_TE),
};

static const rmt_symbol_word_t DALI_SYMBOL_STOP = {
    .level0 = 0,
    .duration0 = DALI_USTORMT(DALI_ONE_TE) * 2,
    .level1 = 0,
    .duration1 = DALI_USTORMT(DALI_ONE_TE) * 2,
};

static esp_err_t dali_rmt_rx_decoder(dali_receivePrevBit_t* receive_prev_bit, uint8_t* backward_frame, uint8_t* backward_frame_index, uint16_t duration, uint16_t level) {
    if ((duration > DALI_USTORMT(DALI_THRESHOLD_1TE_LOW))
            && (duration < DALI_USTORMT(DALI_THRESHOLD_1TE_HIGH))) {
        // short break (1 Te)
        if (((*receive_prev_bit) == DALI_RECEIVE_PREV_BIT_ONE)
                && (level == 0)) {
            // _/-\_/-
            //    ^
            //    ^ ignore this edge
        } else if (((*receive_prev_bit) == DALI_RECEIVE_PREV_BIT_ONE)
                && (level == 1)) {
            // this is a repeated one
            (*backward_frame) <<= 1;
            (*backward_frame) |= 1;
            (*backward_frame_index)++;
            (*receive_prev_bit) = DALI_RECEIVE_PREV_BIT_ONE;
        } else if (((*receive_prev_bit) == DALI_RECEIVE_PREV_BIT_ZERO)
                && (level == 1)) {
            // -\_/-\_
            //    ^
            //    ^ ignore this edge
        } else if (((*receive_prev_bit) == DALI_RECEIVE_PREV_BIT_ZERO)
                && (level == 0)) {
            // this is a repeated zero
            (*backward_frame) <<= 1;
            (*backward_frame_index)++;
            (*receive_prev_bit) = DALI_RECEIVE_PREV_BIT_ZERO;
        }
    } else if ((duration > DALI_USTORMT(DALI_THRESHOLD_2TE_LOW))
            && (duration < DALI_USTORMT(DALI_THRESHOLD_2TE_HIGH))) {
        if (((*receive_prev_bit) == DALI_RECEIVE_PREV_BIT_ONE)
                && (level == 0)) {
            // this is a zero following a one
            (*backward_frame) <<= 1;
            (*backward_frame_index)++;
            (*receive_prev_bit) = DALI_RECEIVE_PREV_BIT_ZERO;
        } else if (((*receive_prev_bit) == DALI_RECEIVE_PREV_BIT_ZERO)
                && (level == 1)) {
            // this is a one following a zero
            (*backward_frame) <<= 1;
            (*backward_frame) |= 1;
            (*backward_frame_index)++;
            (*receive_prev_bit) = DALI_RECEIVE_PREV_BIT_ONE;
        } else {
            // illegal state
            // again, this is somewhere in the middle of a transmission
            // -> do not reset right away, but wait in error state
            return ESP_ERR_INVALID_STATE;
        }
    }

    return ESP_OK;
}

static size_t dali_rmt_tx_encoder_cb(const void *data, size_t data_size,
                               size_t symbols_written, size_t symbols_free,
                               rmt_symbol_word_t *symbols, bool *done, void *arg)
{
    // We need a minimum of 18 symbol spaces to encode a command.
    // Symbol spaces = 1 start bit + 16 bit command + 2 stop bits
    // Commands with more than 2 Bytes cannot be handled.
    if (symbols_free < 18) {
        return 0;
    }

    // Send a start bit first.
    if (symbols_written == 0) {
        symbols[0] = DALI_SYMBOL_ONE;
        return 1;
    }

    // We can calculate where in the data we are from the symbol pos.
    // Divide symbols_written by 8 as each bit translates to one symbol.
    size_t data_pos = (symbols_written - 1) / 8;
    uint8_t *data_bytes = (uint8_t*)data;
    if (data_pos < data_size) {
        // Encode a byte
        size_t symbol_pos = 0;
        for (int bitmask = 0x80; bitmask != 0; bitmask >>= 1) {
            if (data_bytes[data_pos]&bitmask) {
                symbols[symbol_pos++] = DALI_SYMBOL_ONE;
            } else {
                symbols[symbol_pos++] = DALI_SYMBOL_ZERO;
            }
        }
        // We're done; we should have written 16 symbols.
        return symbol_pos;
    } else {
        // Command has been encoded.
        // Add stop bits, and we're done.
        symbols[0] = DALI_SYMBOL_STOP;
        *done = 1; // Indicate end of the transaction.
        return 1;  // We only wrote one symbol
    }
}

static bool dali_rmt_rx_done_cb(rmt_channel_handle_t channel, const rmt_rx_done_event_data_t *edata, void *user_data) {
    BaseType_t high_task_wakeup = pdFALSE;
    QueueHandle_t dali_rxChannelQueue = (QueueHandle_t)user_data;
    // send the received RMT symbols to the parser task
    xQueueSendFromISR(dali_rxChannelQueue, edata, &high_task_wakeup);
    return high_task_wakeup == pdTRUE;
}

esp_err_t dali_init(gpio_num_t dali_rx_gpio, gpio_num_t dali_tx_gpio) {
    CHECK_ARG(dali_rx_gpio && dali_tx_gpio);
    
    // Create RMT RX channel
    dali_rxChannel = NULL;
    rmt_rx_channel_config_t rx_channel_cfg = {
        .clk_src = RMT_CLK_SRC_REF_TICK,
        .resolution_hz = DALI_RMT_RESOLUTION_HZ,
        .mem_block_symbols = 64, // amount of RMT symbols that the channel can store at a time
        .gpio_num = dali_rx_gpio,
        .flags.invert_in = true,
    };
    CHECK_FOR_ERROR(rmt_new_rx_channel(&rx_channel_cfg, &dali_rxChannel));
        
    // Register RX done callback
    dali_rxChannelQueue = xQueueCreate(1, sizeof(rmt_rx_done_event_data_t));
    CHECK_POINTER(dali_rxChannelQueue);
    rmt_rx_event_callbacks_t cbs = {
        .on_recv_done = dali_rmt_rx_done_cb,
    };
    CHECK_FOR_ERROR(rmt_rx_register_event_callbacks(dali_rxChannel, &cbs, dali_rxChannelQueue));

    // Create RMT TX channel
    // The following timing requirement is based on DALI protocol
    dali_rxChannelConfig = (rmt_receive_config_t) {
        .signal_range_min_ns = DALI_USTONS(2),
        .signal_range_max_ns = DALI_USTONS(DALI_THRESHOLD_2TE_HIGH),
    };

    dali_txChannel = NULL;
    dali_txChannelConfig = (rmt_tx_channel_config_t) {
        .clk_src = RMT_CLK_SRC_REF_TICK, // select source clock
        .gpio_num = dali_tx_gpio,
        .mem_block_symbols = 64,
        .resolution_hz = DALI_RMT_RESOLUTION_HZ,
        .trans_queue_depth = 3, // set the number of transactions that can be pending in the background
        .flags.invert_out = true,
    };
    CHECK_FOR_ERROR(rmt_new_tx_channel(&dali_txChannelConfig, &dali_txChannel));

    // Create simple callback-based encoder
    dali_txChannelEncoder = NULL;
    const rmt_simple_encoder_config_t simple_encoder_cfg = {
        .callback = dali_rmt_tx_encoder_cb
        //Note we don't set min_chunk_size here as the default of 64 is good enough.
    };
    CHECK_FOR_ERROR(rmt_new_simple_encoder(&simple_encoder_cfg, &dali_txChannelEncoder));

    // Enable TX channel
    CHECK_FOR_ERROR(rmt_enable(dali_txChannel));

    return ESP_OK;
}

esp_err_t dali_transaction(dali_addressType_t address_type, uint8_t address, bool is_cmd, uint8_t command, bool send_twice, int tx_timeout_ms, int* result) {
    if ((address_type == DALI_ADDRESS_TYPE_SHORT) && (address > 63)) {
        return ESP_ERR_INVALID_ARG;
    }
    if ((address_type == DALI_ADDRESS_TYPE_GROUP) && (address > 15)) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t address_;
    uint8_t tx_buffer[2];
    rmt_rx_done_event_data_t rx_data;
    rmt_symbol_word_t raw_symbols[64];
    uint8_t backward_frame;
    uint8_t backward_frame_index;
    dali_receivePrevBit_t receive_prev_bit;
    rmt_transmit_config_t transmit_config;

    // Reset RX queue
    xQueueReset(dali_rxChannelQueue);

    // Construct DALI address
    // General format is YAAA AAAS where
    // - Y is 0 for short addresses and 1 for group or broadcast
    // - AA AAAA is address
    // - S is 0 for DACP and 1 for commands
    if (address_type == DALI_ADDRESS_TYPE_SPECIAL_CMD) {
        address_ = address;
    } else if (address_type == DALI_ADDRESS_TYPE_BROADCAST) {
        address_ = DALI_ADDRESS_TYPE_BROADCAST_MASK;
        if (is_cmd) {
            address_ |= 1;
        }
    } else {
        if (address_type == DALI_ADDRESS_TYPE_SHORT) {
            address_ = DALI_ADDRESS_TYPE_SHORT_MASK;
        } else {
            address_ = DALI_ADDRESS_TYPE_GROUP_MASK;
        }
        address_ |= (address << 1);
        if (is_cmd) {
            address_ |= 1;
        }
    }

    // Copy address and command to TX buffer for transmission
    tx_buffer[0] = address_;
    tx_buffer[1] = command;

    transmit_config = (rmt_transmit_config_t) {
        .loop_count = 0
    };
    CHECK_FOR_ERROR(rmt_transmit(dali_txChannel, dali_txChannelEncoder, tx_buffer, 2, &transmit_config));
    CHECK_FOR_ERROR(rmt_tx_wait_all_done(dali_txChannel, tx_timeout_ms));

    // Some commands need to be repeated within 100 ms and this is done here
    if (send_twice) {
        vTaskDelay(pdMS_TO_TICKS(DALI_COMMAND_REPEAT_TIME_MS));
        CHECK_FOR_ERROR(rmt_transmit(dali_txChannel, dali_txChannelEncoder, tx_buffer, 2, &transmit_config));
        CHECK_FOR_ERROR(rmt_tx_wait_all_done(dali_txChannel, tx_timeout_ms));
    }

    // If no result is expected, return to caller after a wait time
    if (result == NULL) {
        vTaskDelay(pdMS_TO_TICKS(DALI_BACKWARD_FRAME_TIMEOUT_MS));
        return ESP_OK;
    }

    // Enable RX channel to catch backward frame
    CHECK_FOR_ERROR(rmt_enable(dali_rxChannel));
    CHECK_FOR_ERROR(rmt_receive(dali_rxChannel, raw_symbols, sizeof(raw_symbols), &dali_rxChannelConfig));
    
    // Wait for backward frame to arrive
    if (xQueueReceive(dali_rxChannelQueue, &rx_data, pdMS_TO_TICKS(DALI_BACKWARD_FRAME_TIMEOUT_MS)) == pdPASS) {
        receive_prev_bit = DALI_RECEIVE_PREV_BIT_ONE;
        backward_frame = 0;
        backward_frame_index = 0;
        CHECK_FOR_ERROR(dali_rmt_rx_decoder(&receive_prev_bit, &backward_frame, &backward_frame_index, rx_data.received_symbols[0].duration1, rx_data.received_symbols[0].level1));
        for (size_t i = 1; i < rx_data.num_symbols; i++) {
            CHECK_FOR_ERROR(dali_rmt_rx_decoder(&receive_prev_bit, &backward_frame, &backward_frame_index, rx_data.received_symbols[i].duration0, rx_data.received_symbols[i].level0));
            if (backward_frame_index == 8) {
                break;
            }
            CHECK_FOR_ERROR(dali_rmt_rx_decoder(&receive_prev_bit, &backward_frame, &backward_frame_index, rx_data.received_symbols[i].duration1, rx_data.received_symbols[i].level1));
            if (backward_frame_index == 8) {
                break;
            }
        }
        (*result) = backward_frame;
    } else {
        // Waiting for the backward frame timed out -> no reply was received
        (*result) = DALI_RESULT_NO_REPLY;
    }

    // Disable RX channel as not to catch forward frames
    CHECK_FOR_ERROR(rmt_disable(dali_rxChannel));

    return ESP_OK;
}