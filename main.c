/*
 * main.c
 *
 *  Created on: 24 Oca 2020
 *      Author: ACAKBUDAK
 */

#include "F446RE.h"
#include<stdio.h>
#include<string.h>

uint8_t SetMuniteData[2];
uint8_t SetPointer[1];


int main(void)
{
	i2c1_init();

	ack_enable(ENABLE);

	SetMuniteData[0]=0x00;
	SetMuniteData[1]=0x24;
	SetPointer[0]=0x00;

	i2c1_master_send((uint8_t*)SetMuniteData, 2,0x68,1);

	i2c1_master_send((uint8_t*)SetPointer, 1,0x68,1);

	i2c1_master_recieve(1,0x68,0);


}
