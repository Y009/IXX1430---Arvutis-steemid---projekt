/*
 * main.c
 *      Author: Y009
 */

#include <msp430.h> 
#include <driverlib.h>
#include "clock.h"
#include "gpio.h"
#include "shiftreg.h"
#include <stdio.h>
#include "logic.h"
#include "timer.h"



int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    gpio_init();
    clkInit();
    shiftreg_init();
    logic_init();
    timer_init();

    __bis_SR_register(GIE);

    while(1){
        logic_cyclic();
        shiftreg_exec();
    }


    return 0;
}
