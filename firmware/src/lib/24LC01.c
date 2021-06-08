#include "../mcc_generated_files/system.h"
#include "lib/i2c.h"
#include "24LC01.h"


static void readSingleAddress(uint8_t address)
{
    uint8_t data = 0;
    
    //send the address
    i2c_start();
    i2c_sendByte(EEPROM_WRITE_CMD);
    i2c_sendByte(address);
    i2c_stop();

    //read back the data
    i2c_start();
    i2c_sendByte(EEPROM_READ_CMD);
    data = i2c_readByte(DONT_ACK_EEPROM);
    i2c_nack();
    i2c_stop();

    return data;
}

void EEPROM_Read(uint8_t *pDest, uint8_t address, uint8_t count)
{
    uint8_t i;

    if(address > EEPROM_SIZE){
        return;
    }

    for(i=0 ; i<count ; i++){
        pDest[i] = readSingleAddress(address);
    }
}

uint8_t EEPROM_Read2(uint8_t address)
{
    return readSingleAddress(address);
}

bool EEPROM_Write(uint8_t address, uint8_t new_data)
{
    //we limit (kind of) the maximum EEPROM address
    address &= EEPROM_SIZE;

    i2c_start();
    i2c_sendByte(EEPROM_WRITE_CMD);
    i2c_sendByte(address);
    i2c_sendByte(new_data);
    i2c_stop();

    DELAY_milliseconds(5);

    //now, lets verify the data we've written
    return EEPROM_Read2(address) == new_data;
}
