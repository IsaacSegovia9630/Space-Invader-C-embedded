/*
 * button_status.c
 *
 *  Created on: 29 nov 2022
 *      Author: isaac
 */
#include "fsl_gpio.h"
#include "button_status.h"
#include "Actualizacion_Animacion.h"

static uint8_t g_flag_play = FALSE;

void Buttons_Validation(void)
{
	if(TRUE == g_flag_play)
	{
		if(Ask_Red_Button_Status() == ZERO)
		{
			Shoot();
		}
	}
}

boolean_t Ask_Red_Button_Status(void)
{
	return (boolean_t) ((~GPIO_PinRead(GPIOC, bit_8)) & LOGIC_ONE);
}

void Set_True_Play_Flag_Shoot(void)
{
	g_flag_play = TRUE;
}

void Set_False_Play_Flag_Shoot(void)
{
	g_flag_play = FALSE;
}
