/*
 * MEM.c
 *
 *  Created on: 26/10/2022
 *      Author: Tahirí Ramos
 */
#include "MEM.h"
#include "bits.h"
#include "fsl_gpio.h"
#include "fsl_port.h"


uint8_t Rx_buff_mem[BUFF_MEM];
uint8_t Tx_buff_mem[BUFF_MEM];

uint8_t g_place = 0;

void mem_init(void)
{
	i2c_master_config_t masterConfig;
	uint32_t sourceClock;
	i2c_master_transfer_t masterXfer;

    I2C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Bps = I2C_BAUDRATE;

    sourceClock = I2C_MASTER_CLK_FREQ;

    I2C_MasterInit(EXAMPLE_I2C_MASTER_BASEADDR, &masterConfig, sourceClock);

    //Pone en 0 la estructura de transferencia
    memset(&masterXfer, 0, sizeof(masterXfer));

	uint8_t size = 3;
	uint8_t mem_adress = 0;
	uint8_t MSJ[3] = {0,0,0};
	i2c_master_transfer_t masterXfer_mem;

	for(uint8_t i = 0; i < size; i++)
	{
		Tx_buff_mem[i] = MSJ[i];
	}

    //Que slave quiero, dirección a 7 bits
	masterXfer_mem.slaveAddress   = MEM_MASTER_SLAVE_ADDR_7BIT;
    //Si quiero leer o escribir
	masterXfer_mem.direction      = kI2C_Write;
    //subaddress = Se refiere al registro interno al que queremos afectar
	masterXfer_mem.subaddress     = mem_adress;
    //Que tan grande es en bytes los valores que queremos afectar (memoria = 2, RTC = 1)
	masterXfer_mem.subaddressSize = MEM_ADRESS_LENGTH;
	masterXfer_mem.data           = Tx_buff_mem;
    //DataSize cambia dependiendo de cuantos registros quieres modificar
	masterXfer_mem.dataSize       = size;
	masterXfer_mem.flags          = kI2C_TransferDefaultFlag;

	I2C_MasterTransferBlocking(I2C_MEM_MASTER_BASEADDR, &masterXfer_mem);
}

void write_and_read_mem_init(void)
{
	uint8_t size = 3;
	uint8_t mem_adress = 0;
	uint8_t MSJ[3] = {3,4,5};
	i2c_master_transfer_t masterXfer_mem;

	for(uint8_t i = 0; i < size; i++)
	{
		Tx_buff_mem[i] = MSJ[i];
	}

    //Que slave quiero, dirección a 7 bits
	masterXfer_mem.slaveAddress   = MEM_MASTER_SLAVE_ADDR_7BIT;
    //Si quiero leer o escribir
	masterXfer_mem.direction      = kI2C_Write;
    //subaddress = Se refiere al registro interno al que queremos afectar
	masterXfer_mem.subaddress     = mem_adress;
    //Que tan grande es en bytes los valores que queremos afectar (memoria = 2, RTC = 1)
	masterXfer_mem.subaddressSize = MEM_ADRESS_LENGTH;
	masterXfer_mem.data           = Tx_buff_mem;
    //DataSize cambia dependiendo de cuantos registros quieres modificar
	masterXfer_mem.dataSize       = size;
	masterXfer_mem.flags          = kI2C_TransferDefaultFlag;

	I2C_MasterTransferBlocking(I2C_MEM_MASTER_BASEADDR, &masterXfer_mem);


	i2c_master_transfer_t masterXfer_mem2;

	masterXfer_mem2.slaveAddress   = MEM_MASTER_SLAVE_ADDR_7BIT;
	masterXfer_mem2.direction      = kI2C_Read;
	masterXfer_mem2.subaddress     = mem_adress;
	masterXfer_mem2.subaddressSize = MEM_ADRESS_LENGTH;
	masterXfer_mem2.data           = Rx_buff_mem;
	masterXfer_mem2.dataSize       = size;
	masterXfer_mem2.flags          = kI2C_TransferDefaultFlag;

	I2C_MasterTransferBlocking(I2C_MEM_MASTER_BASEADDR, &masterXfer_mem2);
}

void write_mem(uint8_t MSJ)
{

	i2c_master_transfer_t masterXfer_mem;
	uint8_t mem_adress = 0;
	uint8_t size = 3;

	Tx_buff_mem[g_place] = MSJ;


    //Que slave quiero, dirección a 7 bits
	masterXfer_mem.slaveAddress   = MEM_MASTER_SLAVE_ADDR_7BIT;
    //Si quiero leer o escribir
	masterXfer_mem.direction      = kI2C_Write;
    //subaddress = Se refiere al registro interno al que queremos afectar
	masterXfer_mem.subaddress     = mem_adress;
    //Que tan grande es en bytes los valores que queremos afectar (memoria = 2, RTC = 1)
	masterXfer_mem.subaddressSize = MEM_ADRESS_LENGTH;
	masterXfer_mem.data           = Tx_buff_mem;
    //DataSize cambia dependiendo de cuantos registros quieres modificar
	masterXfer_mem.dataSize       = size;
	masterXfer_mem.flags          = kI2C_TransferDefaultFlag;

	I2C_MasterTransferBlocking(I2C_MEM_MASTER_BASEADDR, &masterXfer_mem);

	g_place++;

	if(3 <= g_place)
	{
		g_place = 0;
	}

}


struct scores read_mem(void)
{
	uint8_t mem_adress = 0;
	uint8_t size = 3;
	struct scores Scores_readed;

	i2c_master_transfer_t masterXfer_mem2;

	masterXfer_mem2.slaveAddress   = MEM_MASTER_SLAVE_ADDR_7BIT;
	masterXfer_mem2.direction      = kI2C_Read;
	masterXfer_mem2.subaddress     = mem_adress;
	masterXfer_mem2.subaddressSize = MEM_ADRESS_LENGTH;
	masterXfer_mem2.data           = Rx_buff_mem;
	masterXfer_mem2.dataSize       = size;
	masterXfer_mem2.flags          = kI2C_TransferDefaultFlag;

	uint8_t state = I2C_MasterTransferBlocking(I2C_MEM_MASTER_BASEADDR, &masterXfer_mem2);

	Scores_readed.Score1 = Rx_buff_mem[0];
	Scores_readed.Score2 = Rx_buff_mem[1];
	Scores_readed.Score3 = Rx_buff_mem[2];

	return Scores_readed;
}

uint8_t mem_communication_test(void)
{
	uint8_t state;
	i2c_master_transfer_t masterXfer_mem;
    //Que slave quiero, dirección a 7 bits
	masterXfer_mem.slaveAddress   = MEM_MASTER_SLAVE_ADDR_7BIT;
    //Si quiero leer o escribir
	masterXfer_mem.direction      = kI2C_Write;
    //subaddress = Se refiere al registro interno al que queremos afectar
	masterXfer_mem.subaddress     = SUB_ADRESS_TEST;
    //Que tan grande es en bytes los valores que queremos afectar (memoria = 2, RTC = 1)
	masterXfer_mem.subaddressSize = MEM_ADRESS_LENGTH;
	masterXfer_mem.data           = Tx_buff_mem;
    //DataSize cambia dependiendo de cuantos registros quieres modificar
	masterXfer_mem.dataSize       = BUFF_MEM;
	masterXfer_mem.flags          = kI2C_TransferDefaultFlag;

	state = I2C_MasterTransferBlocking(I2C_MEM_MASTER_BASEADDR, &masterXfer_mem);

	return state;
}
