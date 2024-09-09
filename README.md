# AT24C256C EEPROM Driver

A simple platform-independent C driver for the AT24C256C EEPROM, designed for embedded systems using I2C communication. The driver provides basic functionality for reading from and writing to the EEPROM, with support for page-wise and address-based operations.

## Features

- **Page-wise Read/Write**: Write and read bytes from a specific page (512 pages, each 64 bytes).
- **Memory Address Read/Write**: Write and read bytes starting from any memory address.
- **Last Address Read**: Read from the last accessed memory address, useful for POST (Power-On Self-Test) tests.

## Requirements

- An I2C-compatible microcontroller.
- Low-level I2C functions and a delay function must be provided by the user.

## Usage

Include the driver header file in your project:

```c
#include "eeprom.h"
```

You need to provide the following low-level functions to handle I2C communication and delays:

- **`i2c_transfer_bytes(uint16_t dev_addr, uint8_t* data, uint8_t nb_of_bytes)`**: Function to send data over I2C.
- **`i2c_read_bytes(uint16_t dev_addr, uint8_t* buf, uint8_t nb_of_bytes)`**: Function to read data over I2C.
- **`delay_ms(uint32_t t_ms)`**: Function to introduce a delay in milliseconds.

Create an instance of the `eeprom_obj_t` structure and initialize it with your low-level function pointers:

```c
eeprom_obj_t eeprom = {
    .i2c_transfer_bytes = my_i2c_transfer_bytes_function,
    .i2c_read_bytes = my_i2c_read_bytes_function,
    .delay_ms = my_delay_function
};
```


## Example

```c
#include "eeprom.h"

// Implement your low-level functions
void my_i2c_transfer_bytes_function(uint16_t dev_addr, uint8_t* data, uint8_t nb_of_bytes) {
    // Your I2C transfer implementation
}

void my_i2c_read_bytes_function(uint16_t dev_addr, uint8_t* buf, uint8_t nb_of_bytes) {
    // Your I2C read implementation
}

void my_delay_function(uint32_t t_ms) {
    // Your delay implementation
}

int main(void) {
    // Create EEPROM object
    eeprom_obj_t eeprom = {
        .i2c_transfer_bytes = my_i2c_transfer_bytes_function,
        .i2c_read_bytes = my_i2c_read_bytes_function,
        .delay_ms = my_delay_function
    };

    uint8_t data_to_write[4] = {0x11, 0x22, 0x33, 0x44};
    uint8_t read_buffer[4];

    // Write to EEPROM
    eeprom_write_bytes(&eeprom, data_to_write, 4, 0x0000);

    // Read from EEPROM
    eeprom_read_bytes(&eeprom, read_buffer, 4, 0x0000);

    // Use the data read
    return 0;
}
```

## License

This project is licensed under the MIT License.
