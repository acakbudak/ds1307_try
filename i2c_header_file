/*
 * i2c_driver.h
 *
 *  Created on: 24 Oca 2020
 *      Author: acakbudak
 */

#ifndef INC_I2C1_DRIVER_H_
#define INC_I2C1_DRIVER_H_

#include "F446RE.h"

#define APB1CLOCK 0x10
#define I2C1_SM_MODE 0
#define I2C1_ACK_ENABLE  1
#define I2C1_ACK_DISABLE 0
#define I2C1_START 8
#define I2C1_STOP 9
#define I2C1_SB_FLAG 1
#define I2C1_ADDR_FLAG 2
#define I2C1_RXNE_FLAG (1 << 6)
#define I2C1_ENABLE 1

void i2c1_init(void);
void ack_enable(uint8_t EnorDi);
void i2c1_master_send(uint8_t Txbuffer, uint32_t Len, uint8_t SlaveAddr,uint8_t Sr);
void i2c1_master_recieve(uint32_t Len, uint8_t SlaveAddr,uint8_t Sr);

#endif /* INC_I2C1_DRIVER_H_ */
