#ifndef __DALI_H__
#define __DALI_H__

#include <stdint.h>
#include <soc/gpio_num.h>
#include <freertos/task.h>

#define DALI_RMT_RESOLUTION_HZ 1000000
#define DALI_USTORMT(x) ((x) * (DALI_RMT_RESOLUTION_HZ / 1000000))
#define DALI_USTONS(x)  (x * 1000)

#define DALI_ONE_TE 416

#define DALI_THRESHOLD_1TE_LOW  334
#define DALI_THRESHOLD_1TE_HIGH 500
#define DALI_THRESHOLD_2TE_LOW  (2*DALI_THRESHOLD_1TE_LOW)
#define DALI_THRESHOLD_2TE_HIGH (2*DALI_THRESHOLD_1TE_HIGH)

#define LSB 1 ///< Index to least significant bit of a 2 byte word
#define MSB 0 ///< Index to most significant bit of a 2 byte word

#define DALI_TX_TIMEOUT_DEFAULT_MS 50

/// A union type to make it easier to access individual bytes of a 16-bit
/// word, and to use as signed or unsigned type.
typedef union SI_UU16
{
  uint16_t u16;   ///< The two byte value as a 16-bit unsigned integer.
  int16_t s16;    ///< The two byte value as a 16-bit signed integer.
  uint8_t u8[2];  ///< The two byte value as two unsigned 8-bit integers.
  int8_t s8[2];   ///< The two byte value as two signed 8-bit integers.
} SI_UU16_t;

typedef enum {
  DALI_ADDRESS_TYPE_SHORT,
  DALI_ADDRESS_TYPE_GROUP,
  DALI_ADDRESS_TYPE_BROADCAST,
  DALI_ADDRESS_TYPE_SPECIAL_CMD
} dali_addressType_t;

/**
 * @brief Initializes the DALI communication interface.
 * 
 * Sets up the specified GPIO pins for DALI RX and TX communication
 * and configures the necessary peripherals for DALI data transmission.
 * 
 * @param dali_rx_gpio GPIO number for the DALI RX (receive) pin.
 * @param dali_tx_gpio GPIO number for the DALI TX (transmit) pin.
 * @return esp_err_t ESP_OK on success or an error code on failure.
 */
esp_err_t dali_init(gpio_num_t dali_rx_gpio, gpio_num_t dali_tx_gpio);

/**
 * @brief Executes a DALI transaction.
 * 
 * Sends a command to a DALI device at the specified address and optionally
 * waits for a response. This function can handle both commands and queries.
 * 
 * @param address_type Type of DALI address (short, group, broadcast, or special command).
 * @param address The DALI address of the target device.
 * @param is_cmd Boolean indicating if the operation is a command (true) or query (false).
 * @param command The DALI command or query to be sent.
 * @param send_twice Boolean indicating if the command should be sent twice.
 * @param timeout_ms Timeout duration in milliseconds for the transaction.
 * @param result Pointer to an integer where the result of the transaction will be stored.
 * @return esp_err_t ESP_OK on success or an error code on failure.
 */
esp_err_t dali_transaction(dali_addressType_t address_type, uint8_t address, bool is_cmd, uint8_t command, bool send_twice, int timeout_ms, int* result);

/**
 * @brief Waits between DALI frames.
 * 
 * A delay function to wait for the required time between DALI frames, ensuring
 * timing compliance in communication.
 */
inline void dali_wait_between_frames(void) __attribute__((always_inline));

inline void dali_wait_between_frames(void) {
    vTaskDelay(pdMS_TO_TICKS(20));
}

#endif // __DALI_H__
