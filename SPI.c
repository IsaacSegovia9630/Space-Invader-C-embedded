
#include "SPI.h"
#include "fsl_dspi.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_clock.h"
#include "clock_config.h"

void SPI_config(void)
{
	dspi_master_config_t masterConfig;
	uint32_t srcClock_Hz;

	CLOCK_SetSimSafeDivs();
	CLOCK_EnableClock(kCLOCK_PortD);	//habilita el reloj en los pines D

	//los pines de los cuales disponemos para usar el SPI
	PORT_SetPinMux(PORTD, PIN0_IDX, kPORT_MuxAlt2); //PTD0; en ALT2 es: SPI0_PCS0
	PORT_SetPinMux(PORTD, PIN1_IDX, kPORT_MuxAlt2); //PTD1; en ALT2 es: SPI0_SCK
	PORT_SetPinMux(PORTD, PIN2_IDX, kPORT_MuxAlt2); //PTD2; en ALT2 es: SPI0_SOUT
	PORT_SetPinMux(PORTD, PIN3_IDX, kPORT_MuxAlt2); //PTD3; en ALT2 es: SPI0_SIN


/* Master config */
	masterConfig.whichCtar 							= kDSPI_Ctar0;
	masterConfig.ctarConfig.baudRate 				= TRANSFER_BAUDRATE;
	masterConfig.ctarConfig.bitsPerFrame 			= FRAME_SIZE;						//	transmite 8 bits de datos por frame
	masterConfig.ctarConfig.cpol					= kDSPI_ClockPolarityActiveHigh;	//CPOL = 0
	masterConfig.ctarConfig.cpha					= kDSPI_ClockPhaseFirstEdge;		//CPHA = 0
	masterConfig.ctarConfig.direction				= kDSPI_MsbFirst;					//la dirección empieza en el MSB (most significant bit)
	masterConfig.ctarConfig.pcsToSckDelayInNanoSec 	= TRANSFER_DELAY / TRANSFER_BAUDRATE;
	masterConfig.ctarConfig.lastSckToPcsDelayInNanoSec = TRANSFER_DELAY / TRANSFER_BAUDRATE;
	masterConfig.ctarConfig.betweenTransferDelayInNanoSec = TRANSFER_DELAY / TRANSFER_BAUDRATE;

	masterConfig.whichPcs = kDSPI_Pcs0;
	masterConfig.pcsActiveHighOrLow = kDSPI_PcsActiveLow; //activo solo cuando el chip select es low

	masterConfig.enableContinuousSCK = false;
	masterConfig.enableRxFifoOverWrite = false;
	masterConfig.enableModifiedTimingFormat = false;
	masterConfig.samplePoint = kDSPI_SckToSin0Clock;

	srcClock_Hz = CLOCK_GetFreq(DSPI0_CLK_SRC);
	DSPI_MasterInit(SPI0, &masterConfig, srcClock_Hz);

}
