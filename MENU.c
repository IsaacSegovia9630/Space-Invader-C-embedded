/*
 * MENU.c
 *
 *  Created on: 28 nov 2022
 *      Author: tahiri
 */

#include "MENU.h"
#include "LCD.h"
#include "Interfaz.h"
#include "Actualizacion_Animacion.h"
#include "MEM.h"

static uint8_t string_2[] = {'0'};
static uint8_t string_3[] = {'0'};
static uint8_t string_4[] = {'0'};

void print_Menu(void)
{
	/*! Strings to be printed in the LCD*/
	uint8_t string_1[] = "SPACE";
	uint8_t string_2[] = "INVADERS";
	uint8_t string_3[] = "1)JUGAR";
	uint8_t string_4[] = "2)VER SCORES";

	LCD_nokia_clear();
	LCD_nokia_goto_xy(25,0); /*! It establishes the position to print the messages in the LCD*/
	LCD_nokia_send_string(string_1); /*! It print a string stored in an array*/
	LCD_nokia_goto_xy(15,1);
	LCD_nokia_send_string(string_2); /*! It print a string stored in an array*/
	LCD_nokia_goto_xy(0,3);
	LCD_nokia_send_string(string_3); /*! It print a string stored in an array*/
	LCD_nokia_goto_xy(0,4);
	LCD_nokia_send_string(string_4); /*! It print a string stored in an array*/
	LCD_nokia_goto_xy(35,5);
	LCD_nokia_send_sprite(INVASOR_3); /*! It print a string stored in an array*/
}

void scores_menu(void)
{

	struct scores Scores = read_mem();

	uint8_t string_1[] = "SCORES";

	if(10 == Scores.Score1)
	{
		string_2[0] = '1';
		string_2[1] = '0';
		string_2[2] = 0;

		string_3[0] = Scores.Score2 + '0';
		string_3[1] = 0;
		string_4[0] = Scores.Score3 + '0';
		string_4[1] = 0;

		LCD_nokia_clear();
		LCD_nokia_goto_xy(25,0); /*! It establishes the position to print the messages in the LCD*/
		LCD_nokia_send_string(string_1); /*! It print a string stored in an array*/
		LCD_nokia_goto_xy(0,2);
		LCD_nokia_send_string(string_2); /*! It print a string stored in an array*/
		LCD_nokia_goto_xy(0,3);
		LCD_nokia_send_string(string_3); /*! It print a string stored in an array*/
		LCD_nokia_goto_xy(0,4);
		LCD_nokia_send_string(string_4); /*! It print a string stored in an array*/
		LCD_nokia_goto_xy(35,5);
		LCD_nokia_send_sprite(INVASOR_3); /*! It print a string stored in an array*/
		return;
	}
	if(10 == Scores.Score2)
	{
		string_3[0] = '1';
		string_3[1] = '0';

		string_2[0] = Scores.Score1 + '0';
		string_2[1] = 0;
		string_4[0] = Scores.Score3 + '0';
		string_4[1] = 0;
	}
	if(10 == Scores.Score3)
	{
		string_4[0] = '1';
		string_4[1] = '0';

		string_2[0] = Scores.Score1 + '0';
		string_2[1] = 0;
		string_3[0] = Scores.Score2 + '0';
		string_3[1] = 0;
	}
	else
	{
		string_2[0] = Scores.Score1 + '0';
		string_2[1] = 0;
		string_3[0] = Scores.Score2 + '0';
		string_3[1] = 0;
		string_4[0] = Scores.Score3 + '0';
		string_4[1] = 0;
	}


	LCD_nokia_clear();
	LCD_nokia_goto_xy(25,0); /*! It establishes the position to print the messages in the LCD*/
	LCD_nokia_send_string(string_1); /*! It print a string stored in an array*/
	LCD_nokia_goto_xy(0,2);
	LCD_nokia_send_num(Scores.Score1); /*! It print a string stored in an array*/
	LCD_nokia_goto_xy(0,3);
	LCD_nokia_send_num(Scores.Score2); /*! It print a string stored in an array*/
	LCD_nokia_goto_xy(0,4);
	LCD_nokia_send_num(Scores.Score3); /*! It print a string stored in an array*/
	LCD_nokia_goto_xy(35,5);
	LCD_nokia_send_sprite(INVASOR_3); /*! It print a string stored in an array*/
}

void select_menu(Menu_states_t state)
{
	switch(state)
	{
		case MENU:
			print_Menu();
		break;

		case PLAY:
			press_button();
		break;

		case SCORES:
			scores_menu();
		break;

		case GAME:
			LCD_nokia_clear();
			frame();
			nave();
			escudos();
			invasores();
		break;

		default:
		break;
	}
}
