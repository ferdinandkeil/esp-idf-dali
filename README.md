# ESP-DALI-LIB

DALI protocol library for ESP-IDF using the RMT peripheral.

## Overview

ESP-DALI-LIB is a DALI (Digital Addressable Lighting Interface) protocol library for the ESP-IDF platform, leveraging the ESP32's RMT (Remote Control) peripheral to manage DALI communication. DALI is a robust lighting control protocol widely used in building automation and lighting systems. This library enables ESP32-based devices to act as a DALI controller, sending and receiving commands from DALI-compatible devices such as dimmers, ballasts, and sensors.

## Features

- **DALI Standard Commands**: Support for standard DALI commands for controlling brightness, scenes, and power states.
- **Query Commands**: Ability to query status, scene levels, and other parameters from DALI devices.
- **Special Commands**: Implementation of special commands, including addressing and device configuration.
- **Data Transfer Register (DTR) Support**: Use of DTR registers for setting configuration parameters.
- **Addressing**: Support for short, group, and broadcast addresses, as well as special addressing modes.
- **Flexible Communication**: Customizable timeouts and adjustable inter-frame delays for communication.

## Requirements

- **ESP-IDF**: ESP32 development framework.
- **ESP32**: Any ESP32-based development board.
- **RMT Peripheral**: The library uses the RMT peripheral to generate and decode the DALI signals.

## Installation

To include this library in your ESP-IDF project:

1. Clone the repository into your project’s `components` folder:
    ```bash
    git clone https://github.com/ferdinandkeil/esp-idf-dali.git components/dali
    ```

2. Configure and build your ESP-IDF project as usual:
    ```bash
    idf.py menuconfig
    idf.py build
    idf.py flash
    ```

## Usage

### Initialization

To begin using the library, initialize the DALI interface with the appropriate GPIO pins for TX and RX:

```c
#include "dali.h"

void app_main() {
    dali_init(GPIO_NUM_21, GPIO_NUM_22);
}
```

### Sending Commands

Use `dali_transaction()` to send commands to DALI devices. The function handles both standard commands (e.g., turning lights on/off, adjusting brightness) and query commands (e.g., checking device status).

```c
#include "dali.h"

int result;

void send_dali_command() {
    esp_err_t status = dali_transaction(DALI_ADDRESS_TYPE_SHORT, 1, true, DALI_COMMAND_ON_AND_STEP_UP, false, DALI_TX_TIMEOUT_DEFAULT_MS, &result);
    if (status == ESP_OK) {
        // Command successfully sent and response received
    }
}
```

### Special Commands

Special commands such as setting the short address or enabling a specific device type can be sent using `dali_transaction` with the correct command codes.

### Using the Data Transfer Register (DTR)

Data Transfer Registers (DTR1 and DTR2) are used for intermediate data storage during configuration. To set values in DTR registers, use the appropriate commands:

```c
dali_transaction(DALI_ADDRESS_TYPE_SPECIAL_CMD, 0, true, DALI_SPECIAL_COMMAND_DATA_TRANSFER_REGISTER_1, false, DALI_TX_TIMEOUT_DEFAULT_MS, &result);
```

### Wait Between Frames

To ensure protocol compliance, use the `dali_wait_between_frames` function to wait between consecutive DALI frames.

```c
dali_wait_between_frames();
```

## Supported DALI Commands

ESP-DALI-LIB supports the following categories of DALI commands:
- **Standard Lighting Commands**: `DALI_COMMAND_ON_AND_STEP_UP`, `DALI_COMMAND_GO_TO_SCENE`, etc.
- **Query Commands**: `DALI_COMMAND_QUERY_STATUS`, `DALI_COMMAND_QUERY_DEVICE_TYPE`, etc.
- **Special Commands**: `DALI_SPECIAL_COMMAND_PROGRAM_SHORT_ADDRESS`, `DALI_SPECIAL_COMMAND_RANDOMISE`, etc.
- **DTR Commands**: Commands for managing Data Transfer Registers.

For a full list of supported commands, refer to `dali.h`.

## Examples

### Basic Example: Turn On Light

```c
#include "dali.h"

void app_main() {
    dali_init(GPIO_NUM_21, GPIO_NUM_22);
    dali_transaction(DALI_ADDRESS_TYPE_SHORT, 1, true, DALI_COMMAND_ON_AND_STEP_UP, false, DALI_TX_TIMEOUT_DEFAULT_MS, NULL);
}
```

### Example: Query Device Status

```c
#include "dali.h"

int result;

void query_status() {
    esp_err_t status = dali_transaction(DALI_ADDRESS_TYPE_SHORT, 1, false, DALI_COMMAND_QUERY_STATUS, false, DALI_TX_TIMEOUT_DEFAULT_MS, &result);
    if (status == ESP_OK && DALI_RESULT_VALID(result)) {
        // Process the device status result
    }
}
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

This README was written using ChatGPT by OpenAI.