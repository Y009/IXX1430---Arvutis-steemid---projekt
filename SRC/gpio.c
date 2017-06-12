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
    P2DIR |= BIT2;
    P2SEL |= BIT2;
    P5SEL |= BIT2 + BIT3;

    GPIO_setAsOutputPin (GPIO_PORT_P6, GPIO_PIN6);     /* Pin 6.6 as row serial data output for shiftreg */
    GPIO_setAsOutputPin (GPIO_PORT_P6, GPIO_PIN3);     /* Pin 6.3 as column serial data output for shiftreg */

    GPIO_setAsOutputPin (GPIO_PORT_P3, GPIO_PIN2);     /* Pin 3.2 as strobe input for shiftreg 1*/
    GPIO_setAsOutputPin (GPIO_PORT_P3, GPIO_PIN3);     /* Pin 3.3 as strobe input for shiftreg 2*/
    GPIO_setAsOutputPin (GPIO_PORT_P3, GPIO_PIN0);     /* Pin 3.0 as strobe input for shiftreg 3*/
    GPIO_setAsOutputPin (GPIO_PORT_P3, GPIO_PIN1);     /* Pin 3.1 as strobe input for shiftreg 4*/

    GPIO_setAsOutputPin (GPIO_PORT_P3, GPIO_PIN4);     /* Pin 3.4 as output enable for all shiftregisters*/

    GPIO_setAsOutputPin (GPIO_PORT_P2, GPIO_PIN4);     /* Pin 2.4 as clock for shiftregisters */

    // use actual offboard buttons (if so, change btn cnfg)?
    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN1);     /* Pin 1.1 as Input for on board button */
    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P2, GPIO_PIN1);     /* Pin 2.1 as Input for on board button */


}


