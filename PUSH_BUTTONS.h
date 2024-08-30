/*
 * PUSH_BUTTONS.h
 *
 * 	This file contains the declarations of functions that we are going to use to manipulate the usage of the push buttons
 * 	integrated in the K64 and externals in case of having them.
 * 	Also we will find some variable definitions and some variable structures that we'll need.
 *
 *  Created on: 31 ago 2022
 *      Author: Hegui Tahirí Ramos Ugalde
 */

#ifndef EQUIPO_6_T5_PUSH_BUTTONS_H_
#define EQUIPO_6_T5_PUSH_BUTTONS_H_

#include "stdint.h"

typedef enum
{
		SW2,	//0
		SW3,	//1
}SW_select_t;

typedef enum
{
	BTN_MENU,
	BTN_1,
	BTN_2
}BTN_select_t;

/*
 * Returns the status of the SW we are asking for. If the sw is pushed will return 0 and if it is
 * not pushed will return a number diferent to 0.
 */
uint8_t sw_status(SW_select_t);

uint8_t btn_status(BTN_select_t);

#endif /* EQUIPO_6_T5_PUSH_BUTTONS_H_ */
