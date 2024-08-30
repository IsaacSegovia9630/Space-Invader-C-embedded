/*
 * config.c
 *
 *  Created on: 6 nov 2022
 *      Author: Tahirí Ramos
 */

#include "config.h"

uint8_t prd = 0xEU;	    //división entre 15 ; 50MHz / 15 = 3.3333e+06; El resultado de la divison tiene que estar entre 2 y 4 MHZ
uint8_t vdl = 0x6U;		//multiplicación por 30 ; 3.3333e+06MHz * 30 = 100,000,000 MHz

void Sistem_Freq_100MHz(void){
	mcg_pll_config_t pll0config =
	{
			.enableMode = MCG_PLL_DISABLE,
			.prdiv = prd,	//división
			.vdiv = vdl,	//multiplicación
	};  /** (50e6/15) * 30 =  100 MHz*/

	const osc_config_t osc_config =
	{
			.freq = 	OSC_FREC,
			.capLoad = (OSC_CAP0P),
			.workMode = kOSC_ModeExt,
			.oscerConfig ={
					.enableMode = kOSC_ErClkEnable,
			}
	};
	CLOCK_SetSimSafeDivs();
	CLOCK_InitOsc0(&osc_config);
	CLOCK_SetXtal0Freq(osc_config.freq);

	CLOCK_SetFbiMode(kMCG_Dmx32Default,kMCG_DrsLow,NULL);
	CLOCK_SetFbeMode(0,kMCG_Dmx32Default,kMCG_DrsLow,NULL);
	CLOCK_SetPbeMode(kMCG_PllClkSelPll0,&pll0config);
	CLOCK_SetPeeMode();
}


