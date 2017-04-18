/*
 * clock.c
 *
 *  Created on: 6. okt 2016 (18 Apr 2017)
 *      Author: Karl (Y009)
 *
 */

/** \file clock.c
**  \brief Documentation for the clock initialisation.
**
**  Basic configuration for master and peripheral clocks.
**/

//***** Header Files **********************************************************
#include <driverlib.h>
#include "clock.h"
    //!TODO! possibly needs to be changed

#define LF_CRYSTAL_FREQUENCY_IN_HZ     32768
#define HF_CRYSTAL_FREQUENCY_IN_HZ     4000000

void
clkInit()
{
/** Function to initialize master and peripheral clock
**
**  Sets proper core voltage level.
**  \n Uses on board XT2 (4Mhz) as a refrence for both clocks.
**/

    PMM_setVCore(PMM_CORE_LEVEL_2);

    UCS_setExternalClockSource(
        LF_CRYSTAL_FREQUENCY_IN_HZ,                                         // XT1CLK input
        HF_CRYSTAL_FREQUENCY_IN_HZ                                          // XT2CLK input
        );

    UCS_turnOnXT2(UCS_XT2_DRIVE_4MHZ_8MHZ);


    UCS_initClockSignal(     /*Clock init using DCO/FLL*/
        UCS_FLLREF,
        UCS_XT2CLK_SELECT,
        UCS_CLOCK_DIVIDER_1
        );


    UCS_initFLLSettle(                      /*Set MCLK and SMCLK to use the DCO/FLL as their oscillator source */
        MCLK_DESIRED_FREQUENCY,
        MCLK_FLLREF_RATIO
        );

}



