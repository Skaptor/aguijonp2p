#include <xc.h>
#include "../mcc_generated_files/system.h"

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

void i2c_nack(void)
{
    I2C2CONbits.ACKDT = 1;
    I2C2CONbits.ACKEN = 1;
}

void i2c_ack(void)
{
    I2C2CONbits.ACKDT = 0;
    I2C2CONbits.ACKEN = 1;
    while(I2C2CONbits.ACKEN);
}

void i2c_sendByte(uint8_t data)
{    
    I2C2TRN = data;
    while(I2C2STATbits.TRSTAT);
    while(I2C2STATbits.TBF);    // 8 clock cycles
    while(!IFS3bits.MI2C2IF);   // Wait for 9th clock cycle
    IFS3bits.MI2C2IF = 0;       // Clear interrupt flag
}

uint8_t i2c_readByte(bool ack)
{
    uint8_t data=0;

    I2C2CONbits.RCEN   = 1;
    while(I2C2CONbits.RCEN);
    I2C2CONbits.RCEN   = 0;
    I2C2STATbits.I2COV = 0;
    data = I2C2RCV;

    if(ack){
        i2c_ack();
    }

    return data;
}




void i2c_init(void)
{   
    I2C2BRG = 0x9D; //100kHz
//    I2C2CON = 0x8000; 
    I2C2CON = 0xC220; 
    I2C2STAT = 0x00;
}

