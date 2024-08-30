/*
 * PIT.h
 *
 *  Created on: 12 sep 2022
 *      Author: tahir
 */

#ifndef EQUIPO_6_T5_PIT_H_
#define EQUIPO_6_T5_PIT_H_

#include "fsl_pit.h"
#include "fsl_common_arm.h"
#include "MK64F12.h"

#define PIT0_IRQ_ID  		PIT0_IRQn
#define PIT1_IRQ_ID  		PIT1_IRQn
#define PIT_BASE_ADDRESS 	PIT
#define PIT_CH_0 			kPIT_Chnl_0
#define PIT_CH_1 			kPIT_Chnl_1
#define WAIT_TIME 			50000u
#define WAIT_TIME2 			317u

typedef enum
{
	PIT0,
	PIT1,
	PIT2,
	PIT3
} PIT_timer_t;

void pit_ch0_init();

void pit_ch1_init();

void PIT_callback_init(PIT_timer_t pit, void(*handler)(void));


#endif /* EQUIPO_6_T5_PIT_H_ */
