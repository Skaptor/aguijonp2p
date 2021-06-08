#ifndef _I2C_H_
#define _I2C_H_

bool i2c_idle(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_stop(void);
void i2c_init(void);
void i2c_ack(void);
void i2c_nack(void);
void i2c_sendByte(uint8_t data);
uint8_t i2c_readByte(bool ack);

#endif
