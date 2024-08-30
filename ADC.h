/*
 * ADC.h
 *
 *  Created on: 10/11/2022
 *      Author: Tahirí
 */

#ifndef ADC_H_
#define ADC_H_

#define INIT_VAL	0U

#include "fsl_adc16.h"
#include "fsl_port.h"
#include "fsl_gpio.h"


#define ADC16_CHANNEL_GROUP 0U
#define ADC16_USER_CHANNEL  15U
#define ADC_RANGE 4096U
#define REFERENCE_VOLTAGE 3.3F

#define PIN1	1U
#define PIN2	2U
#define PIN3	3U
#define PIN18	18U
#define PIN10	10U



/* Esta funcion nos ayudara a configurar el adc */
void ADC_init(void);

/* Esta funcion nos ayudara a obtener el valos del ADC */
uint16_t ADC_get_value(void);


#endif /* ADC_H_ */
