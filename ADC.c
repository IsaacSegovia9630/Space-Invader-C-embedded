/*
 * ADC.c
 *
 *  Created on: 10/11/2022
 *      Author: Tahirí
 */

#include "ADC.h"


static adc16_channel_config_t g_adc16ChannelConfigStruct;

void ADC_init(void){
		adc16_config_t adc16ConfigStruct;

		/* PORTB10 (pin 55) is configured as ADC0_SE12 */
		PORT_SetPinMux(PORTC, 1, kPORT_PinDisabledOrAnalog);

		ADC16_GetDefaultConfig(&adc16ConfigStruct);
		#ifdef BOARD_ADC_USE_ALT_VREF
			adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;
		#endif
		ADC16_Init(ADC0, &adc16ConfigStruct);
		ADC16_EnableHardwareTrigger(ADC0, false); /* Make sure the software trigger is used. */
		g_adc16ChannelConfigStruct.channelNumber                        = ADC16_USER_CHANNEL;
		g_adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;
		#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
			g_adc16ChannelConfigStruct.enableDifferentialConversion = false;
		#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */
}

uint16_t ADC_get_value(void)
{
	uint16_t ADC_value = 0;
	ADC16_SetChannelConfig(ADC0, ADC16_CHANNEL_GROUP, &g_adc16ChannelConfigStruct);
	while (INIT_VAL == (kADC16_ChannelConversionDoneFlag &
					ADC16_GetChannelStatusFlags(ADC0, ADC16_CHANNEL_GROUP)))
			{
			}
	ADC_value = ADC16_GetChannelConversionValue(ADC0, ADC16_CHANNEL_GROUP);
	return ADC_value;
}

