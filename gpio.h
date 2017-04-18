/*
 * gpio.h
 *
 *  Created on: 16. okt 2016 (18 Apr 2017)
 *      Author: Y009
 */

/** \file gpio.h
**  \brief Documentation for the gpio module's header.
**
**  Global macro defines.
**/

#ifndef GPIO_H_
#define GPIO_H_

//***** Defines ***************************************************************

// Getting all used gpio calls to go through the gpio module to preserve hierachy.

/**
** \def gpio_getPinInput(port, pin)                 GPIO_getInputPinValue(port, pin)
**  \brief Sets local gpio to appropriate board function of similar name.
**
** Gets \b port \b pin's logical value.
**/

/**
** \def gpio_setPinHigh(port, pin)              GPIO_setOutputHighOnPin(port, pin)
**  \brief Sets local gpio to appropriate board function of similar name.
**
** Sets \b port's \b pin to a logical 1
**/

/**
** \def gpio_setPinLow(port, pin)               GPIO_setOutputLowOnPin(port, pin)
**  \brief Sets local gpio to appropriate board function of similar name.
**
** Sets \b port's \b pin to a logical 0
**/

/**
** \def gpio_getInterrupt(port, pin)                GPIO_getInterruptStatus(port, pin)
**  \brief Sets local gpio to appropriate board function of similar name.
**
** Gets \b port \b pin's pending interrupt status.
**/

/**
** \def gpio_setInterruptEdge(port, pin, edge)      GPIO_selectInterruptEdge(port, pin, edge)
**  \brief Sets local gpio to appropriate board function of similar name.
**
** Sets \b port's \b pin interrupt status to be set by either a falling or a rising edge.
**/

/**
** \def gpio_clearInterrupt(port, pin)              GPIO_clearInterrupt(port, pin)
**  \brief Sets local gpio to appropriate board function of similar name.
**
** Used to clear serviced interrupts on \b port's \b pin
**/

/**
** \def gpio_getInterrupt(port, pin)                GPIO_getInterruptStatus(port, pin)
**  \brief Sets local gpio to appropriate board function of similar name.
**
** Sets \b port's pin to a logical 1
**/

#define gpio_getPinInput(port, pin)                 GPIO_getInputPinValue(port, pin)
#define gpio_setPinHigh(port, pin)                  GPIO_setOutputHighOnPin(port, pin)
#define gpio_setPinLow(port, pin)                   GPIO_setOutputLowOnPin(port, pin)
#define gpio_getInterrupt(port, pin)                GPIO_getInterruptStatus(port, pin)
#define gpio_setInterruptEdge(port, pin, edge)      GPIO_selectInterruptEdge(port, pin, edge)
#define gpio_clearInterrupt(port, pin)              GPIO_clearInterrupt(port, pin)

//*****************************************************************************
//
// The following are values that can be passed to the port parameter
// for macros :gpio_getPinInput, gpio_setPinHigh, gpio_setPinLow, gpio_getInterrupt,
// gpio_setInterruptEdge and clearInterrupt
//
//*****************************************************************************

#define gpio_PORT_P1                        GPIO_PORT_P1
#define gpio_PORT_P2                        GPIO_PORT_P2
#define gpio_PORT_P3                        GPIO_PORT_P3
#define gpio_PORT_P4                        GPIO_PORT_P4
#define gpio_PORT_P5                        GPIO_PORT_P5
#define gpio_PORT_P6                        GPIO_PORT_P6
#define gpio_PORT_P7                        GPIO_PORT_P7
#define gpio_PORT_P8                        GPIO_PORT_P8
#define gpio_PORT_P9                        GPIO_PORT_P9
#define gpio_PORT_P10                       GPIO_PORT_P10
#define gpio_PORT_P11                       GPIO_PORT_P11
#define gpio_PORT_PA                        GPIO_PORT_PA
#define gpio_PORT_PB                        GPIO_PORT_PB
#define gpio_PORT_PC                        GPIO_PORT_PC
#define gpio_PORT_PD                        GPIO_PORT_PD
#define gpio_PORT_PE                        GPIO_PORT_PE
#define gpio_PORT_PF                        GPIO_PORT_PF
#define gpio_PORT_PJ                        GPIO_PORT_PJ

//*****************************************************************************
//
// The following are values that can be passed to the pin parameter
// for macros :gpio_getPinInput, gpio_setPinHigh, gpio_setPinLow, gpio_getInterrupt,
// gpio_setInterruptEdge and clearInterrupt
//
//*****************************************************************************

#define gpio_PIN0                           GPIO_PIN0
#define gpio_PIN1                           GPIO_PIN1
#define gpio_PIN2                           GPIO_PIN2
#define gpio_PIN3                           GPIO_PIN3
#define gpio_PIN4                           GPIO_PIN4
#define gpio_PIN5                           GPIO_PIN5
#define gpio_PIN6                           GPIO_PIN6
#define gpio_PIN7                           GPIO_PIN7
#define gpio_PIN8                           GPIO_PIN8
#define gpio_PIN9                           GPIO_PIN9
#define gpio_PIN10                          GPIO_PIN10
#define gpio_PIN11                          GPIO_PIN11
#define gpio_PIN12                          GPIO_PIN12
#define gpio_PIN13                          GPIO_PIN13
#define gpio_PIN14                          GPIO_PIN14
#define gpio_PIN15                          GPIO_PIN15
#define gpio_PIN_ALL8                       GPIO_PIN_ALL8
#define gpio_PIN_ALL16                      GPIO_PIN_ALL16

//*****************************************************************************
//
// The following are values that can be passed to the edge parameter
// for macro : gpio_setInterruptEdge
//
//*****************************************************************************
#define gpio_HIGH_TO_LOW_TRANSITION         GPIO_HIGH_TO_LOW_TRANSITION
#define gpio_LOW_TO_HIGH_TRANSITION         GPIO_LOW_TO_HIGH_TRANSITION

//***** Prototypes *************************************************
/** \cond IGNORE*/
void gpio_init(void);
/** \endcond IGNORE*/

#endif /* GPIO_H_ */
