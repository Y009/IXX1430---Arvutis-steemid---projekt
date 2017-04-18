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
    // use actual offboard buttons (if so, change btn cnfg)?
    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN1);     /* Pin 1.1 as Input for on board button */
    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P2, GPIO_PIN1);     /* Pin 2.1 as Input for on board button */

}


