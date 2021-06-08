#include <xc.h>
#include "mcc_generated_files/system.h"

void i2c_idle(void)
{
    while((I2C2CON & 0x001F ) || I2C2STATbits.S || I2C2STATbits.P);
}

void i2c_start(void)
{
    I2C2CONbits.SEN = 1;    // Initiate Start on SDA and SCL pins
    while(I2C2CONbits.SEN); // Wait till start sequence is completed
}

void i2c_stop(void)
{
    I2C2CONbits.PEN = 1;    // Initiate Stop on SDA and SCL pins
    while(I2C2CONbits.PEN); // Wait till stop sequence is completed
}

void i2c_sendByte(uint8_t data)
{    
    I2C2TRN = data;
    while(I2C2STATbits.TRSTAT);
    while(I2C2STATbits.TBF);    // 8 clock cycles
    while(!IFS3bits.MI2C2IF);   // Wait for 9th clock cycle
    IFS3bits.MI2C2IF = 0;       // Clear interrupt flag
}


void i2c_init(void)
{   
    I2C2BRG = 0x9D; //100kHz
    I2C2CON = 0x8000; 
    I2C2STAT = 0x00;
}

