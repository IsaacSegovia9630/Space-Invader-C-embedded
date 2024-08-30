/*
 * Actualizacion_Animacion.c
 *
 *  Created on: 28 nov 2022
 *      Author: ie721714
 */
#include "Actualizacion_Animacion.h"
#include "ADC.h"
#include "LCD.h"
#include "Interfaz.h"
#include "button_status.h"
#include "Sounds.h"
#include "bits.h"
#include "MEM.h"


static uint8_t x_ship_position = INITIAL_X_SHIP_POSITION;

static uint32_t g_Invasors_Movement_Counter = 0;

static uint32_t g_Shoot_Counter = 0;

static uint8_t g_Play_Flag = FALSE;

static uint8_t g_Score = 0;

static uint8_t g_Defeat_enemies = 0;

static uint8_t g_flag_show_game_over = TRUE;

static uint8_t g_flag_move_invasor_right = TRUE;

struct Shoot_Structure Shoots[MAX_NUM_SHOOTS] =
{
		{0,0,TRUE}
};

struct Invader_Structure Invaders[MAX_NUM_INVADERS] =
{
		{0,0,TRUE,0,0,FALSE,0},{0,0,TRUE,0,0,FALSE,0},{0,0,TRUE,0,0,FALSE,0},{0,0,TRUE,0,0,FALSE,0},{0,0,TRUE,0,0,FALSE,0},
		{0,0,TRUE,0,0,FALSE,0},{0,0,TRUE,0,0,FALSE,0},{0,0,TRUE,0,0,FALSE,0},{0,0,TRUE,0,0,FALSE,0},{0,0,TRUE,0,0,FALSE,0}
};

void Refresh_Ship_Position_and_Music(void)
{
	if(TRUE == g_Play_Flag)
	{
		g_Shoot_Counter++;
		g_Invasors_Movement_Counter++;

		if(MAX_NUM_INVADERS == g_Defeat_enemies)
		{
			if(TRUE == g_flag_show_game_over)
			{
				game_over();
				g_flag_show_game_over = FALSE;
			}

		}

		if(10 <= g_Invasors_Movement_Counter)
		{
			if(TRUE == g_flag_move_invasor_right)
			{
				for(int i = MAX_NUM_INVADERS-1; i >= 0; i--)
				{
					if(Invaders[i].Available == TRUE)
					{

						LCD_nokia_goto_xy(Invaders[i].x_invader_position, Invaders[i].y_invader_position);
						LCD_nokia_send_sprite(CLEAR_SPRITE);

						Invaders[i].x_invader_position = Invaders[i].x_invader_position + 4;

						if(69 <= Invaders[i].x_invader_position)
						{
							g_flag_move_invasor_right = FALSE;

							Invaders[i].x_invader_position = Invaders[i].x_invader_position - 4;
							LCD_nokia_goto_xy(Invaders[i].x_invader_position, Invaders[i].y_invader_position);
							LCD_nokia_send_sprite(INVASOR_1);
							return;
						}

						LCD_nokia_goto_xy(Invaders[i].x_invader_position, Invaders[i].y_invader_position);
						LCD_nokia_send_sprite(INVASOR_1);
					}

				}
			}
			else
			{
				for(int i = 0; i < MAX_NUM_INVADERS; i++)
				{
					if(Invaders[i].Available == TRUE)
					{
						LCD_nokia_goto_xy(Invaders[i].x_invader_position, Invaders[i].y_invader_position);
						LCD_nokia_send_sprite(CLEAR_SPRITE);

						Invaders[i].x_invader_position = Invaders[i].x_invader_position - 4;

						if(1 >= Invaders[i].x_invader_position)
						{
							g_flag_move_invasor_right = TRUE;

							Invaders[i].x_invader_position = Invaders[i].x_invader_position + 4;
							LCD_nokia_goto_xy(Invaders[i].x_invader_position, Invaders[i].y_invader_position);
							LCD_nokia_send_sprite(INVASOR_1);
							return;
						}

						LCD_nokia_goto_xy(Invaders[i].x_invader_position, Invaders[i].y_invader_position);
						LCD_nokia_send_sprite(INVASOR_1);
					}

				}
			}

			g_Invasors_Movement_Counter = 0;
		}

		if(10 <= g_Shoot_Counter)
		{
			for(int j = 0; j < MAX_NUM_INVADERS; j++)
			{
				if((TRUE == Invaders[j].explosion_state) && (TRUE == Invaders[j].Available))
				{
					Invaders[j].explosion_counter++;
					if(2 <= Invaders[j].explosion_counter)
					{
						LCD_nokia_goto_xy(Invaders[j].x_explosion_position, Invaders[j].y_explosion_position);
						LCD_nokia_send_sprite(CLEAR_SPRITE);
						Invaders[j].explosion_state = FALSE;
						Invaders[j].Available = FALSE;
					}
				}
			}

			for(int i = 0; i < MAX_NUM_SHOOTS; i++)
			{
				if(FALSE == Shoots[i].Available)
				{
					//clear the shoot that would be move
					LCD_nokia_goto_xy(Shoots[i].x_shoot_position, Shoots[i].y_shoot_position);
					LCD_nokia_send_sprite_Laser(Clear_Laser);

					//Move the cursor for he new shoot
					Shoots[i].y_shoot_position--;

					//Check if a Shoot has reach the limit of the screen
					if(255  == Shoots[i].y_shoot_position)
					{
						Shoots[i].Available = TRUE;
						return;
					}

					//Check if a invader have been destroyed
					for(int j = 0; j < MAX_NUM_INVADERS; j++)
					{

						if( (Invaders[j].x_invader_position <= Shoots[i].x_shoot_position) && (Invaders[j].x_invader_position+10 >= Shoots[i].x_shoot_position) && (Invaders[j].y_invader_position == Shoots[i].y_shoot_position) && (Invaders[j].Available == TRUE) && (Invaders[j].explosion_state == FALSE))
						{
							LCD_nokia_goto_xy(Invaders[j].x_invader_position, Invaders[j].y_invader_position);
							LCD_nokia_send_sprite(EXPLOSION);
							Invaders[j].x_explosion_position = Invaders[j].x_invader_position;
							Invaders[j].y_explosion_position = Invaders[j].y_invader_position;
							Invaders[j].explosion_state = TRUE;

							Shoots[i].Available = TRUE;

							g_Score++;
							g_Defeat_enemies++;

							LCD_nokia_goto_xy(60,5);
							LCD_nokia_send_num(g_Score);

							return;
						}
					}

					//Print the shoot in the new position
					LCD_nokia_goto_xy(Shoots[i].x_shoot_position, Shoots[i].y_shoot_position);
					LCD_nokia_send_sprite_Laser(Laser);
				}
			}

			g_Shoot_Counter = 0;
		}

		uint16_t Adc_Value = ADC_get_value();

		//If we get this case, it means that the joystick has not been moved
		if(LOW_DEAD_ZONE  <= Adc_Value && HIGH_DEAD_ZONE >= Adc_Value)
		{
			return;
		}

		//If we get this case, it means that the joystick has  been moved to the right
		if(VALUE_MOVE_LEFT >=  Adc_Value)
		{
			x_ship_position++;

			if(MAX_POSITION_RIGHT_SCREEN  < x_ship_position)
			{
				x_ship_position--;
			}

			LCD_nokia_goto_xy(x_ship_position, DEFAULT_Y_SHIP_POSITION);
			LCD_nokia_send_sprite(NAVE);
			return;
		}

		//If we get this case, it means that the joystick has  been moved to the left
		if( VALUE_MOVE_RIGHT  <= Adc_Value)
		{
			x_ship_position--;

			if( MAX_POSITION_LEFT_SCREEN > x_ship_position)
			{
				x_ship_position++;
			}

			LCD_nokia_goto_xy(x_ship_position, DEFAULT_Y_SHIP_POSITION);
			LCD_nokia_send_sprite(NAVE);
			return;
		}
	}
}

void Shoot(void)
{
	for(int i = 0; i < MAX_NUM_SHOOTS; i++)
	{
		if(TRUE == Shoots[i].Available)
		{
			Shoots[i].Available = FALSE;

			Shoots[i].x_shoot_position = x_ship_position + X_Laser_Offset;
			Shoots[i].y_shoot_position = DEFAULT_Y_SHIP_POSITION - Y_Laser_Offset;

			LCD_nokia_goto_xy(Shoots[i].x_shoot_position, Shoots[i].y_shoot_position);
			LCD_nokia_send_sprite_Laser(Laser);

			return;
		}
	}
}

void Set_True_Play_Flag_Movement(void)
{
	g_Play_Flag = TRUE;
}

void Set_False_Play_Flag_Movement(void)
{
	g_Play_Flag = FALSE;
}

void Set_Position_Invaders(uint8_t x_position,uint8_t y_position,uint8_t invader)
{
	Invaders[invader].x_invader_position = x_position;
	Invaders[invader].y_invader_position = y_position;
}

void Reset_Game_Values(void)
{
	for(int i = 0; i < MAX_NUM_SHOOTS; i++)
	{
		Shoots[i].x_shoot_position = 0;
		Shoots[i].y_shoot_position = 0;
		Shoots[i].Available = TRUE;
	}

	for(int i = 0; i < MAX_NUM_INVADERS; i++)
	{
		Invaders[i].x_invader_position = 0;
		Invaders[i].y_invader_position = 0;
		Invaders[i].Available = TRUE;
		Invaders[i].x_explosion_position = 0;
		Invaders[i].y_explosion_position = 0;
		Invaders[i].explosion_state = FALSE;
		Invaders[i].explosion_counter = 0;
	}

	x_ship_position = INITIAL_X_SHIP_POSITION;

	g_Defeat_enemies = 0;

	g_flag_show_game_over = TRUE;

	write_mem(g_Score);

	g_Score = 0;
}
