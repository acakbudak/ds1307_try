/*
 * i2c1_driver.c
 *
 *  Created on: 24 Oca 2020
 *      Author: ACAKBUDAK
 */

#include "i2c1_driver.h"

static void address_send_write(uint8_t slave_addr)
{
	slave_addr = (slave_addr << 1);
	slave_addr &= ~(1);
	I2C1->DR = slave_addr;
}

static void address_send_read(uint8_t slave_addr)
{
	slave_addr = (slave_addr << 1);
	slave_addr |= 1;
	I2C1->DR = slave_addr;
}

static void start_transmission(void)
{
	I2C1->CR1 |= (1 << I2C1_START);
}

static void stop_transmission(void)
{
	I2C1->CR1 |= (1 << I2C1_STOP);
}


static void ADDR_FLAG_CLEAR(void)
{
	uint8_t dummy_read;
	dummy_read = I2C1->SR1;
	dummy_read = I2C1->SR2;
}

/*
 * PB6 is used for i2c1_scl
 * PB7 is used for i2c1_sda
 */
void i2c1_init(void)
{
//	i2c1 clock enable
	RCC->APB1ENR |= (1 << 21);
//	GPIOB clock enable
	RCC->AHB1ENR |= (1 << 1);

//	gpio configs for i2c1_scl and i2c1_sda
	GPIOB->MODER |= (0xA << 12);
	GPIOB->OTYPER |= (3 << 6);
	GPIOB->AFR[0] |= (0x44 << 24);
	GPIOB->PUPDR |= (5 << 12);
	GPIOB->OSPEEDR |= (0xA << 12);

	I2C1->CR1 |= I2C1_ENABLE;
	I2C1->CR2 |= APB1CLOCK;

//	CCR and TRISE configs 16mhz Apb in standard mode
	I2C1->CCR |= (I2C1_SM_MODE << 15);
	I2C1->CCR |= 0x50;
	I2C1->TRISE |= 0x17;


}



void ack_enable(uint8_t EnorDi)
{
	if(EnorDi==ENABLE)
		I2C1->CR1 |= (I2C1_ACK_ENABLE << 10);
	else if(EnorDi==DISABLE)
		I2C1->CR1 |= (I2C1_ACK_DISABLE << 10);

}
void i2c1_master_send(uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr,uint8_t Sr)
{
	// 1. Generate the START condition
	start_transmission();

	//2. confirm that start generation is completed by checking the SB flag in the SR1
	while(!(I2C1->SR1 & I2C1_SB_FLAG));

	//3. Send the address of the slave with r/nw bit set to w(0) (total 8 bits )
	address_send_write(SlaveAddr);

	//4. Confirm that address phase is completed by checking the ADDR flag in the SR1
	while(!(I2C1->SR1 & I2C1_ADDR_FLAG));

	//5. clear the ADDR flag according to its software sequence
	ADDR_FLAG_CLEAR();

	if(Len==1)
	I2C1->DR = *pTxbuffer;

	if(Len>1)
	{
		for(uint8_t i=0; i<2;i++)
		{
			while(!(I2C1->SR1 & I2C1_TXE_FLAG));
			I2C1->DR = *pTxbuffer;
			pTxbuffer++;
		}
	}
	stop_transmission();


}

void i2c1_master_recieve(uint32_t Len, uint8_t SlaveAddr,uint8_t Sr)
{
	uint8_t Rxbuffer=0;

	// 1. Generate the START condition
	start_transmission();

	//2. confirm that start generation is completed by checking the SB flag in the SR1
	while(!(I2C1->SR1 & I2C1_SB_FLAG));

	//3. Send the address of the slave with r/nw bit set to r(1) (total 8 bits )
	address_send_read(SlaveAddr);

	//4. Confirm that address phase is completed by checking the ADDR flag in the SR1
	while(!(I2C1->SR1 & I2C1_ADDR_FLAG));

	//Disabling acking first
	ack_enable(DISABLE);

	//clear the ADDR flag according to its software sequence
	ADDR_FLAG_CLEAR();

	//wait until  RXNE becomes 1
	while(!(I2C1->SR1 & I2C1_RXNE_FLAG));

	stop_transmission();

	//read data in to buffer
	Rxbuffer = I2C1->DR;

	//re-enable ACKing
	ack_enable(ENABLE);

	(void)Rxbuffer;

}
