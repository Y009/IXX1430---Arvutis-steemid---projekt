/*
 * clock.h
 *
 *  Created on: 6. okt 2016 (18. april 2017)
 *      Author: Karl (Y009)
 */

/** \file clock.h
**  \brief Documentation for the clock's header.
**
**  Global macro defines.
**/

#ifndef CLOCK_H_
#define CLOCK_H_

    //!TODO! possibly needs to be changed
//***** Defines ***************************************************************
#define MCLK_DESIRED_FREQUENCY  16000                /**< desired clock frequency in Khz */
#define MCLK_FLLREF_RATIO              MCLK_DESIRED_FREQUENCY / 4000    /**< Ratio of desired clock frequency to refrence clock frequency */


/** \cond IGNORE*/
//***** Prototypes *************************************************
void clkInit(void);
/** \endcond IGNORE*/
#endif /* CLOCK_H_ */
