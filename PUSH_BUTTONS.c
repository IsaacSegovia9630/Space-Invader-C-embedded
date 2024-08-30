/*
 * PUSH_BUTTONS.c
 *
 * Contains the definitions of all the functions declared in the PUSH_BUTTONS header file.
 *
 *  Created on: 31 ago 2022
 *      Author: Hegui Tahirí Ramos Ugalde
 */

#include "bits.h"
#include "PUSH_BUTTONS.h"
#include "fsl_gpio.h"
#include "GPIO.h"

const uint8_t LOGIC_ONE = 0X1;

uint8_t sw_status(SW_select_t sw_num)
{
	switch(sw_num)
	{
		case SW2:
		// returns the value of the SW2, if it is pushed in = 0 other wise is != 0
		return (boolean_t) ((~GPIO_PinRead(GPIOC, bit_6)) & LOGIC_ONE);
		break;
		case SW3:
			// returns the value of the SW3, if it is pushed in = 0 other wise is != 0
			return (boolean_t) ((~GPIO_PinRead(GPIOA, bit_4)) & LOGIC_ONE);
		break;
		default:
			return FALSE;
		break;
	}
}

uint8_t btn_status(BTN_select_t btn_num)
{
	switch(btn_num)
	{
		case BTN_MENU:
			// returns the value of the BTN_Menu, if it is pushed in = 0 other wise is != 0
			return (boolean_t) ((~GPIO_PinRead(GPIOC, bit_0)) & LOGIC_ONE);
		break;
		case BTN_1:
		// returns the value of the BTN_Menu, if it is pushed in = 0 other wise is != 0
		return (boolean_t) ((~GPIO_PinRead(GPIOC, bit_8)) & LOGIC_ONE);
		break;
		case BTN_2:
			// returns the value of the BTN_1, if it is pushed in = 0 other wise is != 0
			return (boolean_t) ((~GPIO_PinRead(GPIOC, bit_9)) & LOGIC_ONE);
		break;
		default:
			return FALSE;
		break;
	}
}

