/*
 * MENU.h
 *
 *  Created on: 28 nov 2022
 *      Author: tahiri
 */

#ifndef PROYECTO_FINAL_EQUIPO_6_T5_MENU_H_
#define PROYECTO_FINAL_EQUIPO_6_T5_MENU_H_

typedef enum
{
	MENU,
	PLAY,
	SCORES,
	GAME
}Menu_states_t;

void print_Menu(void);

void scores_menu(void);

void select_menu(Menu_states_t state);

#endif /* PROYECTO_FINAL_EQUIPO_6_T5_MENU_H_ */
