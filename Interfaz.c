/*
 * Interfaz.c
 *
 *  Created on: 28 nov 2022
 *      Author: tahiri
 */

#include "Interfaz.h"
#include "LCD.h"
#include "LCD_nokia_images.h"
#include "Delay.h"
#include "Actualizacion_Animacion.h"

uint8_t num_1 = 3;
uint8_t counter_x = 1;
uint8_t counter_y = 0;

extern const uint8_t space_invaders_logo[PIC_SIZE];
extern const uint8_t game_frame[PIC_SIZE];
extern const uint8_t press_any_button[PIC_SIZE];
extern const uint8_t game_over_frame[PIC_SIZE];

void logo(void)
{
	LCD_nokia_clear();/*! It clears the information printed in the LCD*/
	LCD_nokia_bitmap(space_invaders_logo); /*! It prints an array that hold an image, in this case is the initial picture*/
	delay(65000);
}

void press_button(void)
{
	LCD_nokia_clear();/*! It clears the information printed in the LCD*/
	LCD_nokia_bitmap(press_any_button); /*! It prints an array that hold an image, in this case is the initial picture*/
	delay(65000);
}

void game_over(void)
{
	LCD_nokia_clear();/*! It clears the information printed in the LCD*/
	LCD_nokia_bitmap(game_over_frame); /*! It prints an array that hold an image, in this case is the initial picture*/
	delay(65000);

}

void escudos(void)
{
	LCD_nokia_goto_xy(15,3);
	LCD_nokia_send_sprite(ESCUDO);
	LCD_nokia_goto_xy(35,3);
	LCD_nokia_send_sprite(ESCUDO);
	LCD_nokia_goto_xy(55,3);
	LCD_nokia_send_sprite(ESCUDO);
}

void invasores(void)
{
	counter_x = 1;
	counter_y = 0;

	for(int i = 0; i < MAX_NUM_INVADERS; i++){
		if(50 <= counter_x)
		{
			counter_x = 1;
			counter_y++;
		}
		if(3 <= counter_y)
		{
			counter_y = 0;
		}
		else
		{
			LCD_nokia_goto_xy(counter_x, counter_y);
			LCD_nokia_send_sprite(INVASOR_1);
			Set_Position_Invaders(counter_x, counter_y, i);
			counter_x = counter_x + 10;
		}
	}
}

void nave(void)
{
	LCD_nokia_goto_xy(35,4);
	LCD_nokia_send_sprite(NAVE);
}

void frame(void)
{
	uint8_t score = 0;

	LCD_nokia_clear();/*! It clears the information printed in the LCD*/
	LCD_nokia_bitmap(game_frame); /*! It prints an array that hold an image, in this case is the initial picture*/

	delay(65000);
	LCD_nokia_goto_xy(8,5);
	LCD_nokia_send_num(num_1);
	delay(65000);
	LCD_nokia_goto_xy(60,5);
	LCD_nokia_send_num(score);
	delay(65000);
}

void menu(void)
{

}
