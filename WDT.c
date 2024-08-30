/*
 * WDT.c
 *
 *  Created on: 30 sep 2022
 *      Author: Tahirí Ramos
 */
#include "WDT.h"
#include "fsl_wdog.h"
#include "fsl_rcm.h"
#include "bits.h"
#include "PIT.h"

#define WDOG_WCT_INSTRUCITON_COUNT (256U)
#define Time_For_Reset 0x3E8U

static WDOG_Type *wdog_base = WDOG;
static RCM_Type *rcm_base   = RCM;

uint16_t wdog_reset_count = 0;
wdog_config_t config;

static void WaitWctClose(WDOG_Type *base)
{
    /* Accessing register by bus clock */
    for (uint32_t i = 0; i < WDOG_WCT_INSTRUCITON_COUNT; i++)
    {
        (void)base->RSTCNT;
    }
}
/*!
 * @brief Gets the Watchdog timer output.
 *
 * @param base WDOG peripheral base address
 * @return Current value of watchdog timer counter.
 */
static inline uint32_t GetTimerOutputValue(WDOG_Type *base)
{
    return (uint32_t)((((uint32_t)base->TMROUTH) << bit_16) | (base->TMROUTL));
}

void wdt_init(void)
{

    WDOG_GetDefaultConfig(&config);
    //Value of cycles to execute the WDT (WDT = 1KHz)
    config.timeoutValue = Time_For_Reset;
    //Se configuran los registros
    WDOG_Init(wdog_base, &config);
    //Cierra la ventana de tiempo del WDT
    WaitWctClose(wdog_base);

    /*If not wdog reset*/
    if (!(RCM_GetPreviousResetSources(rcm_base) & kRCM_SourceWdog))
    {
        WDOG_ClearResetCount(wdog_base);
    }
    wdog_reset_count = WDOG_GetResetCount(wdog_base);
}

void feed_dog(void)
{
	WDOG_Refresh(WDOG);
    while (GetTimerOutputValue(wdog_base) < (config.timeoutValue >> bit_3))
    {
    }
}

