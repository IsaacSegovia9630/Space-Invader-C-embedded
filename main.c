/*
 * Proyecto Final Equipo 6
 *
 * Autores: Hegui Tahirí Ramos Ugalde
 * 			Isaac Segovia Hernandez
 *
 */

#include "SPI.h"
#include "WDT.h"
#include "LCD.h"
#include "LCD_nokia_images.h"
#include "GPIO.h"
#include "Delay.h"
#include "Interfaz.h"
#include "ADC.h"
#include "Actualizacion_Animacion.h"
#include "PIT.h"
#include "NVIC.h"
#include "button_status.h"
#include "Sounds.h"
#include "DAC.h"
#include "config.h"
#include "PUSH_BUTTONS.h"
#include "MENU.h"
#include "MEM.h"

int main(void) {

	uint8_t g_flag_menu = TRUE;
	uint8_t g_flag_play = FALSE;
	uint8_t g_flag_scores = FALSE;

	uint8_t g_flag_show_menu   = TRUE;
	uint8_t g_flag_show_play = TRUE;
	uint8_t g_flag_show_scores = TRUE;

	Sistem_Freq_100MHz();
	gpio_init();
	btns_init();
	SPI_config();
	ADC_init();
	dac_init();
	I2C_pins_init();
	mem_init();

	LCD_nokia_init(); /*! Configuration function for the LCD */

	logo();
	delay(700000);

	pit_ch0_init();

	PIT_callback_init(PIT0, Refresh_Ship_Position_and_Music);

	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enable_interrupt_and_priority(PORTC_IRQ,PRIORITY_4);

	NVIC_enable_interrupt_and_priority(PIT_CH0_IRQ,PRIORITY_5);

	GPIO_callback_init(GPIO_C, Buttons_Validation);

	wdt_init();

	while(1)
	{
		feed_dog();

		if(TRUE == g_flag_menu)
		{
			if(TRUE == g_flag_show_menu)
			{
				select_menu(MENU);
				g_flag_show_menu = FALSE;
			}

			if(TRUE == btn_status(BTN_1))
			{
				g_flag_menu = FALSE;
				g_flag_play = TRUE;
				g_flag_scores = FALSE;
			}
			if(TRUE == btn_status(BTN_2))
			{
				g_flag_menu = FALSE;
				g_flag_play = FALSE;
				g_flag_scores = TRUE;
			}
		}
		if(TRUE == g_flag_play)
		{
			if(TRUE == g_flag_show_play)
			{
				g_flag_show_play = FALSE;

				select_menu(GAME);
				Set_True_Play_Flag_Shoot();
				Set_True_Play_Flag_Movement();

			}

			if(TRUE == btn_status(BTN_MENU))
			{
				g_flag_menu = TRUE;
				g_flag_play = FALSE;
				g_flag_scores = FALSE;

				g_flag_show_menu = TRUE;
				g_flag_show_play = TRUE;
				g_flag_show_scores = TRUE;

				Set_False_Play_Flag_Shoot();
				Set_False_Play_Flag_Movement();
				Reset_Game_Values();

				select_menu(MENU);
			}
		}
		if(TRUE == g_flag_scores)
		{
			if(TRUE == g_flag_show_scores)
			{
				select_menu(SCORES);
				g_flag_show_scores = FALSE;
			}

			if(TRUE == btn_status(BTN_MENU))
			{
				g_flag_menu = TRUE;
				g_flag_play = FALSE;
				g_flag_scores = FALSE;

				g_flag_show_menu = TRUE;
				g_flag_show_play = TRUE;
				g_flag_show_scores = TRUE;

				select_menu(MENU);
			}
		}
	}
	return 0 ;

}
