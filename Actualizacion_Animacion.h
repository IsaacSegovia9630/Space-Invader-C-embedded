/*
 * Actualizacion_Animacion.h
 *
 *  Created on: 28 nov 2022
 *      Author: ie721714
 */

#ifndef ACTUALIZACION_ANIMACION_H_
#define ACTUALIZACION_ANIMACION_H_

#include <stdint.h>

#define INITIAL_X_SHIP_POSITION 35
#define DEFAULT_Y_SHIP_POSITION 4
#define LOW_DEAD_ZONE 2020
#define HIGH_DEAD_ZONE 2045
#define VALUE_MOVE_LEFT 2019
#define VALUE_MOVE_RIGHT 2046
#define MAX_POSITION_RIGHT_SCREEN 71
#define MAX_POSITION_LEFT_SCREEN 1
#define X_Laser_Offset 4
#define Y_Laser_Offset 1
#define MAX_NUM_INVADERS 10
#define MAX_NUM_SHOOTS 1
#define INITIAL_X_SHIP_POSITION 35

#define MAIN_MUSIC_DURATION 140

struct Shoot_Structure
{
	uint8_t x_shoot_position;
	uint8_t y_shoot_position;
	uint8_t Available;
};

struct Invader_Structure
{
	uint32_t x_invader_position;
	uint32_t y_invader_position;
	uint8_t Available;
	uint8_t x_explosion_position;
	uint8_t y_explosion_position;
	uint8_t explosion_state;
	uint8_t explosion_counter;
};

void Refresh_Ship_Position_and_Music(void);

void Shoot(void);

void Set_True_Play_Flag_Movement(void);

void Set_False_Play_Flag_Movement(void);

void Set_Position_Invaders(uint8_t,uint8_t,uint8_t);

void Reset_Game_Values(void);

#endif /* ACTUALIZACION_ANIMACION_H_ */
