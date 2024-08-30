/*
 * DMA.c
 *
 *  Created on: 12 may 2022
 *      Author: Tahirí
 */

#include "DMA.h"
#include "NVIC.h"
#include "DAC.h"
#include "Sounds.h"


volatile bool g_Transfer_Done = false;

uint8_t contador = 0;

AT_QUICKACCESS_SECTION_DATA_ALIGN(edma_tcd_t tcdMemoryPoolPtr[TCD_QUEUE_SIZE + 1], sizeof(edma_tcd_t));

edma_handle_t g_EDMA_Handle;


void EDMA_Callback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
    if (transferDone)
    {
        g_Transfer_Done = true;
    }
}

void init_DMA_sound(uint16_t *addr, uint32_t sound_size)
{
	edma_transfer_config_t transferConfig;
	edma_config_t userConfig;

	NVIC_enable_interrupt_and_priority(DMA_CH0_IRQ, PRIORITY_5);
	NVIC_global_enable_interrupts;

	DMAMUX_Init(DMAMUX0);

	DMAMUX_SetSource(DMAMUX0, 0, DMA_SOURCE_GPIO);

	DMAMUX_EnablePeriodTrigger(DMAMUX, 0);

	DMAMUX_EnableChannel(DMAMUX0, 0);

	EDMA_GetDefaultConfig(&userConfig);
	EDMA_Init(DMA0, &userConfig);
	EDMA_CreateHandle(&g_EDMA_Handle, DMA0, 0);
	EDMA_SetCallback(&g_EDMA_Handle, EDMA_Callback, NULL);
	EDMA_ResetChannel(g_EDMA_Handle.base, g_EDMA_Handle.channel);

	EDMA_PrepareTransferConfig(&transferConfig,
			   &addr[0],
			   2,				/*16 bits, tamaño de source en bytes*/
			   2, 				/* source offset */
			   &DAC0->DAT[0],
			   2,				/*16 bits, tamaño de destino en bytes*/
			   0,               /* dest offset */
			   2,             /* minor loop bytes: 8*/
			   sound_size*2); /* major loop counts : 4, tamaño del arreglo x2*/
    EDMA_TcdSetMajorOffsetConfig(
					   tcdMemoryPoolPtr, //param tcd A point to the TCD structure.
					   0, //* param sourceOffset source address offset. restar el tamaño del arreglo x2
					   -sound_size*2);//destOffset destination address offset.

   EDMA_TcdSetTransferConfig(tcdMemoryPoolPtr, &transferConfig, NULL);

   EDMA_TcdEnableInterrupts(&tcdMemoryPoolPtr[0], kEDMA_MajorInterruptEnable);
   EDMA_TcdEnableAutoStopRequest(&tcdMemoryPoolPtr[0], true);
   EDMA_InstallTCD(DMA0, 0, &tcdMemoryPoolPtr[0]);
   EDMA_EnableChannelRequest(DMA0, 0);
}
