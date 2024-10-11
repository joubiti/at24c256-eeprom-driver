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


#include "eeprom.h"

#define EEPROM_WRITE_ADDR        0xA0
#define EEPROM_READ_ADDR         0xA1
#define WRITE_CYCLE_TIME          5

#define PAGE_SIZE       64
#define PAGE_ADDRESS(x) (64 * x)


void eeprom_write_bytes_to_page(eeprom_obj_t* obj, const uint8_t* data, uint8_t nb_of_bytes, uint8_t page_number){
    uint8_t cmds[2+nb_of_bytes];
    // send word address bytes (MSB first)
    cmds[0] = (PAGE_ADDRESS(page_number) >> 8) & 0xFF;
    cmds[1] = (PAGE_ADDRESS(page_number) & 0xFF);
    for (uint8_t j = 0; j < nb_of_bytes; j ++){
        cmds[j+2] = data[j];
    }
    obj->i2c_transfer_bytes(EEPROM_WRITE_ADDR, cmds, sizeof(cmds));
    obj->delay_ms(WRITE_CYCLE_TIME);
}


void eeprom_read_bytes_from_page(eeprom_obj_t* obj, uint8_t* buf, uint8_t nb_of_bytes, uint8_t page_number){
    uint8_t cmds[2];
    // send word address bytes (MSB first)
    cmds[0] = (PAGE_ADDRESS(page_number) >> 8) & 0xFF;
    cmds[1] = (PAGE_ADDRESS(page_number) & 0xFF);
    // dummy write
    obj->i2c_transfer_bytes(EEPROM_WRITE_ADDR, cmds, sizeof(cmds));
    // read bytes from EEPROM
    obj->i2c_read_bytes(EEPROM_READ_ADDR, buf, nb_of_bytes);
}

void eeprom_write_bytes(eeprom_obj_t* obj, const uint8_t* data, uint8_t nb_of_bytes, uint16_t memory_address){
    uint8_t cmds[2+nb_of_bytes];
    cmds[0] = (memory_address >> 8) & 0xFF;
    cmds[1] = (memory_address & 0xFF);
    for (uint8_t j = 0; j < nb_of_bytes ; j ++){
        cmds[j + 2] = data[j];
    }
    obj->i2c_transfer_bytes(EEPROM_WRITE_ADDR, cmds, sizeof(cmds));
    obj->delay_ms(WRITE_CYCLE_TIME);
}

void eeprom_read_bytes(eeprom_obj_t* obj,  uint8_t* buf, uint8_t nb_of_bytes, uint16_t memory_address){
    uint8_t cmds[2];
    // send word address bytes (MSB first)
    cmds[0] = (memory_address >> 8) & 0xFF;
    cmds[1] = (memory_address & 0xFF);
    // dummy write
    obj->i2c_transfer_bytes(EEPROM_WRITE_ADDR, cmds, sizeof(cmds));
    // read bytes from EEPROM
    obj->i2c_read_bytes(EEPROM_READ_ADDR, buf, nb_of_bytes);
}













