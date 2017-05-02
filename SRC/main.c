#include <msp430.h> 
#include <driverlib.h>
#include "clock.h"
#include "gpio.h"
#include "shiftreg.h"
#include <stdio.h>

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    gpio_init();
    shiftreg_init();

    while(1){
        shiftreg_exec();
    }
    return 0;
}
