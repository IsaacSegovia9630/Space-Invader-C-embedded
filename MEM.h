
/*
 * MEM.h
 *
 *	configuración para el funcionamiento y uso de la memoria externa
 *  Created on: 26/10/2022
 *      Author: Tahirí
 */

#ifndef MEM_H_
#define MEM_H_

#include "fsl_i2c.h"
#include "PIT.h"
#include "MK64F12.h"
#include "NVIC.h"



#define I2C_MEM_MASTER_CLK_SRC          I2C0_CLK_SRC
#define I2C_MEM_MASTER_CLK_FREQ         CLOCK_GetFreq(I2C0_CLK_SRC)
#define I2C_MEM_MASTER_BASEADDR 		I2C0

#define MEM_MASTER_SLAVE_ADDR_7BIT	 0x50U
#define MEM_ADRESS_LENGTH    		 0x02
#define BUFF_MEM					 9U
#define I2C_MASTER_SLAVE_ADDR_7BIT   0x6FU
#define EXAMPLE_I2C_MASTER_BASEADDR I2C0
#define I2C_MASTER_CLK_FREQ         CLOCK_GetFreq(I2C0_CLK_SRC)
#define I2C_BAUDRATE               400000U

#define SUB_ADRESS_TEST   0x0U

void mem_init(void);

void write_and_read_mem_init(void);

void write_mem(uint8_t MSJ);

uint8_t mem_communication_test(void);

struct scores
{
	uint8_t Score1;
	uint8_t Score2;
	uint8_t Score3;
};

/*
 * lee lo que tiene guardado la memoria y me regresa un estado en falso o verdadero para verificar si leyó
 */
struct scores read_mem(void);



#endif /* MEM_H_ */
