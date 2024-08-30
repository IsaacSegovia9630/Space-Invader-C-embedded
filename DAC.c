/*
 * DAC.c
 *
 * Contains the definitions of funtions declared on file DAC.h
 *
 *  Created on: 11 sep 2022
 *      Author: Tahirí Ramos
 *
 */

#include "DAC.h"
#include "bits.h"
#include "fsl_dac.h"

#define INDEX_ZERO 0U

void dac_init(void)
{
	dac_config_t dacConfigStruct;
	//initialize DAC configuration struct
    DAC_GetDefaultConfig(&dacConfigStruct);
    //initialize DAC module
    DAC_Init(DAC0, &dacConfigStruct);
    DAC_Enable(DAC0, TRUE);
    //sets the current read pointer of the DAC buffer
    DAC_SetBufferReadPointer(DAC0, INDEX_ZERO);
}

