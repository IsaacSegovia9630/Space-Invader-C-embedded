/*
 * config.h
 *
 *  Created on: 6 nov 2022
 *      Author: Tahirí
 */

#ifndef EQUIPO_6_P3_CONFIG_H_
#define EQUIPO_6_P3_CONFIG_H_

#include "fsl_clock.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MCG_IRCLK_DISABLE 0U                   /*!< MCGIRCLK disabled */
#define MCG_PLL_DISABLE 0U                     /*!< MCGPLLCLK disabled */
#define OSC_CAP0P 0U                           /*!< Oscillator 0pF capacitor load */
#define OSC_ER_CLK_DISABLE 0U                  /*!< Disable external reference clock */

#define OSC_FREC 		50000000U /*Frecuencia de cristal externo 50MHz*/

/*
 * para cambiar la frecuencia de la k64 a 60Mhz
 */
void Sistem_Freq_100MHz(void);


#endif /* EQUIPO_6_P3_CONFIG_H_ */
