/*
 * timer.c
 *
 *  Created on: 23. okt 2016 (18 Apr 2017)
 *      Author: Y009
 */

/** \file timer.c
**  \brief Documentation for the timer module.
**
**  Describes the workings of the timer module.
**  Is used to debounce a button press.
**/

//***** Header Files **********************************************************
#include <driverlib.h>
#include "timer.h"

//***** DEFINES ***************************************************************

    //!TODO! find faster rate based on new clk

#define TIMETO 0x1F40                           /**< 0.5 ms cycle for timer A. Calculated with 16MHz SMCLK with divider 1 */
unsigned long long int interruptCounter;        /**< Times the timer A interrupt has to taken place */

short timerFlag = 0 ;                           /**< Flag to check whether an interrupt has occured or not. */

/*********************************************************/
void
timer_init(void)
/** Initializes Timer A in up mode with TIMETO ms cycle time.
**/
{
    Timer_A_initUpModeParam initUpParam = { 0 };
        initUpParam.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;                      /* Use SMCLK (faster clock) */
        initUpParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;           /* Input clock = SMCLK / 1 = 16MHz */
        initUpParam.timerPeriod = TIMETO;                                         /* 0.5ms */
        initUpParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE;    /* Enable TAR -> 0 interrupt */
        initUpParam.captureCompareInterruptEnable_CCR0_CCIE =
                TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE;                               /* Enable CCR0 compare interrupt */
        initUpParam.timerClear = TIMER_A_DO_CLEAR;                                /* Clear TAR & clock divider */
        initUpParam.startTimer = false;                                           /* Don't start the timer, yet */
    Timer_A_initUpMode( timer_timerBase, &initUpParam );                          /* Set up Timer A0 */

    //*************************************************************************
    //  Clear/enable interrupt flags and start timer
    //*************************************************************************
    Timer_A_clearTimerInterrupt( timer_timerBase );                               /* Clear TA0IFG */
    Timer_A_clearCaptureCompareInterrupt( timer_timerBase,
        TIMER_A_CAPTURECOMPARE_REGISTER_0                                         /* Clear CCR0IFG interrupt pending flag bit */
    );

    Timer_A_startCounter(
        timer_timerBase,
        TIMER_A_UP_MODE
    );
}

/*********************************************************/
void
timer_checkFlag()
/** Checks whether there has been a timer interrupt and increments a counter if so.
**
**  Is called from application level in every cycle.
**  timerFlag is set to true whenever a timer A interrupt has occurred.
**  Is used to get a delay of TIMETO * interruptCounter.
**/
{
    timer_diTAI(timer_timerBase);
    if(timerFlag){
        interruptCounter++;
        timerFlag = 0;                  /* Clear timerA interrupt up flag */
    }
    timer_enTAI(timer_timerBase);
}

/*********************************************************/
int
timer_getCounter(void)
/** Get timerA's interruptCounter.
**
**  \return interruptCounter
**/
{
    return interruptCounter;
}

//*****************************************************************************
// Interrupt Service Routines
//*****************************************************************************
#pragma vector=TIMER0_A0_VECTOR         /*< Interrupt vector pragma for timerA0. */
__interrupt
void
timer_debouncingBtn (void)
/** Interrupt vector for timerA0.
**
**  Is triggered when the timerA's value reaches TIMETO and resets back to 0.
**/
{
    timerFlag = 1;
    Timer_A_clearTimerInterrupt(timer_timerBase);                                       /* Clear TA0IFG */
}
