/*
 * gameTimer.h
 *
 *  Created on: 18 Apr 2017
 *      Author: Y009
 */

#ifndef GAMETIMER_H_
#define GAMETIMER_H_

//***** Defines ***************************************************************

/**
** \def counter_enTBI(timerBase)            Timer_B_enableInterrupt(timerBase)
**  \brief Sets local gpio to appropriate board function of similar name.
**
** Enables interrupts by \b timerBase timer.
**/

/**
** \def counter_diTBI(timerBase)            Timer_B_disableInterrupt(timerBase)
**  \brief Sets local gpio to appropriate board function of similar name.
**
** Disables interrupts by \b timerBase timer.
**/

/**
** \def counter_getCountValue(timerBase)    Timer_B_getCounterValue(timerBase);
**  \brief Sets local gpio to appropriate board function of similar name.
**
**  Gets the current timer value form \b timerBase timer.
**/

#define gameTimer_enTBI(timerBase)            Timer_B_enableInterrupt(timerBase)          /* Enable interrupts by Timer B */
#define gameTimer_diTBI(timerBase)            Timer_B_disableInterrupt(timerBase)         /* Disable interrupts by Timer B */
#define gameTimer_getCountValue(timerBase)    Timer_B_getCounterValue(timerBase);

#define counter_timerBase                   TIMER_B0_BASE                       /**< The used timer's timerBase for the counter module */

/** \cond IGNORE*/
unsigned long long int counter_getOverflow(void);
void counter_init(void);
/** \endcond IGNORE*/
#endif /* GAMETIMER_H_ */
