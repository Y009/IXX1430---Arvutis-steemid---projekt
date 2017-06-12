/*
 * main.c
 *      Author: Y009
 */

#include <msp430.h> 
#include <driverlib.h>
#include "clock.h"
#include "gpio.h"
#include "shiftreg.h"
#include "logic.h"
#include "timer.h"

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    gpio_init();
    clkInit();
    shiftreg_init();
    logic_init();

    __bis_SR_register(GIE);     // Enable global interrupts

    while(1){
        shiftreg_exec();
        logic_cyclic();
    }

    return 0;
}
