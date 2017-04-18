/*
 * gameTimer.c
 *
 *  Created on: 18 Apr 2017
 *      Author: Y009
 */

//***** Header Files **********************************************************
#include <driverlib.h>
#include "gameTimer.h"

//***** DEFINES ***************************************************************

    //!TODO! calculate a more suitable speed

#define TIMETO 0xFDE8                       /**< 32.5 ms cycle for timer A. Calculated with 16MHz SMCLK with divider 16 */
unsigned long long int timerB_overflow;     /**< Maximum time; Will only result in false data when it overflow itself. ~4 years */

/*********************************************************/
unsigned long long int
gameTimer_getOverflow(void)
/** Get timerA's interruptCounter.
**
**  \return timerB_overflow
**/
{
  return timerB_overflow;
}

/*********************************************************/
void
gameTimer_init(void)
/** Initializes Timer B in up mode with TIMETO ms cycle time.
**/
{
    Timer_B_initUpModeParam initUpParam = { 0 };
        initUpParam.clockSource = TIMER_B_CLOCKSOURCE_SMCLK;                        /* Use SMCLK (faster clock) */
        initUpParam.clockSourceDivider = TIMER_B_CLOCKSOURCE_DIVIDER_16;            /* Input clock = SMCLK / 1 = 16MHz */
        initUpParam.timerPeriod = TIMETO;                                           /* 32.5ms - dec: 65 000*/
        initUpParam.timerInterruptEnable_TBIE = TIMER_B_TBIE_INTERRUPT_ENABLE;      /* Enable TAR -> 0 interrupt */
        initUpParam.captureCompareInterruptEnable_CCR0_CCIE =
                TIMER_B_CCIE_CCR0_INTERRUPT_ENABLE;                                 /* Enable CCR0 compare interrupt */
        initUpParam.timerClear = TIMER_B_DO_CLEAR;                                  /* Clear TAR & clock divider */
        initUpParam.startTimer = false;                                             /* Don't start the timer, yet */
    Timer_B_initUpMode( counter_timerBase, &initUpParam );                          /* Set up Timer A0 */

    //*************************************************************************
    //  Clear/enable interrupt flags and start timer
    //*************************************************************************

    Timer_B_clearTimerInterrupt( counter_timerBase );                               /* Clear TA0IFG */
    Timer_B_clearCaptureCompareInterrupt( counter_timerBase,
        TIMER_B_CAPTURECOMPARE_REGISTER_0                                           /* Clear CCR0IFG interrupt pending flag bit */
    );

    Timer_B_startCounter(
        counter_timerBase,
        TIMER_B_UP_MODE
    );
}

//*****************************************************************************
// Interrupt Service Routines
//*****************************************************************************
#pragma vector=TIMER0_B0_VECTOR             /*< Interrupt vector pragma for timerB0. */
__interrupt
void
gameTimer_addToTimer (void)
/** Interrupt vector for timerB0.
**
**  Is triggered when the timerB's value reaches TIMETO and resets back to 0.
**/
{
    timerB_overflow++;
    Timer_B_clearTimerInterrupt(counter_timerBase);                                     /* Clear TB0IFG */
}


