/*
 * gpio.c
 *
 *  Created on: 18 Apr 2017
 *      Author: Y009
 */


//***** Header Files **********************************************************
#include <driverlib.h>
#include "gpio.h"

void
gpio_init()
/** Initializes the used pins on the board.
**/
{
    //!TODO! Figure out pins for shiftreg.
    P2DIR |= GPIO_PIN2;              // clock for shiftreg
    P2SEL |= GPIO_PIN2;              /* clock set */
    GPIO_setAsOutputPin (GPIO_PORT_P6, GPIO_PIN6);     /* Pin 6.6 as serial data output for shiftreg */
    GPIO_setAsOutputPin (GPIO_PORT_P3, GPIO_PIN2);     /* Pin 3.2 as strobe input for shiftreg*/

    // use actual offboard buttons (if so, change btn cnfg)?
    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN1);     /* Pin 1.1 as Input for on board button */
    //GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P2, GPIO_PIN1);     /* Pin 2.1 as Input for on board button */


}


