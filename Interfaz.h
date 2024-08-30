/*
 * Interfaz.h
 *
 *  Created on: 28 nov 2022
 *      Author: tahiri
 */

#ifndef PROYECTO_FINAL_EQUIPO_6_T5_INTERFAZ_H_
#define PROYECTO_FINAL_EQUIPO_6_T5_INTERFAZ_H_


#define INVASOR_1	 0
#define INVASOR_2	 1
#define EXPLOSION 	 2
#define NAVE 		 3
#define ESCUDO		 4
#define DEAD_INV	 5
#define LASER 		 6
#define INVASOR_3	 7
#define CLEAR_SPRITE 8

typedef enum
{
	Laser,
	Clear_Laser
}Laser_t;

void logo(void);

void press_button(void);

void game_over(void);

void escudos(void);

void invasores(void);

void nave(void);

void frame(void);

void menu(void);

#endif /* PROYECTO_FINAL_EQUIPO_6_T5_INTERFAZ_H_ */
