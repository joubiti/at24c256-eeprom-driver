/**
 * @file eeprom.h
 * @author joubiti (github.com/joubiti)
 * @brief AT24C256 EEPROM driver
 * @version 0.1
 * @date 2024-09-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include "stdint.h"

/**
 * @brief EEPROM object structure, contains function pointers to I2C low level functions and delay function
 * 
 */
typedef struct{
    void(*i2c_transfer_bytes)(uint16_t dev_addr, uint8_t* data, uint8_t nb_of_bytes);
    void(*i2c_read_bytes)(uint16_t dev_addr, uint8_t* buf, uint8_t nb_of_bytes);
    void(*delay_ms)(uint32_t t_ms);
}eeprom_obj_t;

/**
 * @brief Writes a number of bytes sequentially from the starting address of an EEPROM page
 * 
 * @param obj: pointer to EEPROM object
 * @param data: array of bytes
 * @param nb_of_bytes: number of bytes
 * @param page_number: index of page (512 pages in total, from 0 to 511) 
 */
void eeprom_write_bytes_to_page(eeprom_obj_t* obj, const uint8_t* data, uint8_t nb_of_bytes, uint8_t page_number);

/**
 * @brief Reads a number of bytes sequentially from the starting address of an EEPROM page
 * 
 * @param obj: pointer to EEPROM object 
 * @param buf: buffer
 * @param nb_of_bytes: number of bytes to read
 * @param page_number: index of page (512 pages in total, from 0 to 511)
 */
void eeprom_read_bytes_from_page(eeprom_obj_t* obj, uint8_t* buf, uint8_t nb_of_bytes, uint8_t page_number);

/**
 * @brief Write a number of bytes starting from a memory address in EEPROM
 * 
 * @param obj: pointer to EEPROM object
 * @param data: array of bytes
 * @param nb_of_bytes: number of bytes
 * @param memory_address: 16-bit memory address
 */
void eeprom_write_bytes(eeprom_obj_t* obj, const uint8_t* data, uint8_t nb_of_bytes, uint16_t memory_address);

/**
 * @brief Reads a number of bytes starting from a memory address in EEPROM
 * 
 * @param obj: pointer to EEPROM object
 * @param buf: data buffer
 * @param nb_of_bytes: number of bytes
 * @param memory_address: 16-bit memory address
 */
void eeprom_read_bytes(eeprom_obj_t* obj,  uint8_t* buf, uint8_t nb_of_bytes, uint16_t memory_address);

