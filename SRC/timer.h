/*
 * timer.h
 *
 *  Created on: 23. okt 2016 (18 Apr 2017)
 *      Author: Y009
 */

/** \file timer.h
**  \brief Documentation for the timer module's header.
**
**  Global macro defines.
**/

#ifndef TIMER_H_
#define TIMER_H_

//***** Defines ***************************************************************

/**
** \def timer_enTAI(timerBase)      Timer_A_enableInterrupt(timerBase)
**  \brief Sets local gpio to appropriate board function of similar name.
**
** Enables interrupts by \b timerBase timer.
**/

/**
** \def timer_diTAI(timerBase)      Timer_A_disableInterrupt(timerBase)
**  \brief Sets local gpio to appropriate board function of similar name.
**
** Disables interrupts by \b timerBase timer.
**/

#define timer_enTAI(timerBase)      Timer_A_enableInterrupt(timerBase)
#define timer_diTAI(timerBase)      Timer_A_disableInterrupt(timerBase)

#define timer_timerBase             TIMER_A0_BASE           /**< The used timer's timerBase for the timer module */

/** \cond IGNORE*/
void timer_init(void);
int timer_getCounter(void);
void set_timerCounter();
void timer_checkFlag();
/** \endcond IGNORE*/

#endif /* TIMER_H_ */
