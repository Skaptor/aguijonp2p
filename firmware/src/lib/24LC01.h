#ifndef _24LC01_H
#define _24LC01_H

//refer to 24LC01B datasheet
#define EEPROM_SIZE         0x7F
#define EEPROM_WRITE_CMD    0xA0
#define EEPROM_READ_CMD     0xA1

#define ACK_EEPROM          true
#define DONT_ACK_EEPROM     false

void EEPROM_Read(uint8_t *pDest, uint8_t address, uint8_t count);
uint8_t EEPROM_Read2(uint8_t address);
bool EEPROM_Write(uint8_t address, uint8_t new_data);

#endif
