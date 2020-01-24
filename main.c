/*
 * main.c
 *
 *  Created on: 24 Oca 2020
 *      Author: lenovo
 */

#include "F446RE.h"

uint8_t data1=0x01;
uint8_t data2=0x04;
uint8_t data3=0x05;

int main(void)
{
	i2c1_init();

	ack_enable(ENABLE);

	i2c1_master_send(data2,1,0x68,0);
	i2c1_master_recieve(1,0x68,0);
	i2c1_master_send(data2,1,0x68,0);
	i2c1_master_recieve(1,0x68,0);
	i2c1_master_send(data3,1,0x68,0);
	i2c1_master_recieve(1,0x68,0);


}
