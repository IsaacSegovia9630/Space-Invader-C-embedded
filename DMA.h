/*
 * DMA.h
 *
 *  Created on: 12 may 2022
 *      Author: HP
 */

#ifndef DMA_H_
#define DMA_H_

#include "bits.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_edma.h"
#include "NVIC.h"
#include "GPIO.h"
#include "fsl_dmamux.h"
#include "fsl_pit.h"
#include "PIT.h"


#define ARR_SIZE (16u)
#define BUFFER_LENGTH       8
#define TCD_QUEUE_SIZE      1U

#define DMA_SOURCE_GPIO (59u)

#define DMA_SOURCE_PIT (58u)
#define PIT_BASEADDR PIT

/*
 * callback del EDMA
 */
void EDMA_Callback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds);
/*
 * Inicializamos el DMA
 */
void init_DMA_sound(uint16_t *addr, uint32_t sound_size);


#endif /* DMA_H_ */
