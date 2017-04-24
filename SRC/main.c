#include <msp430.h> 
#include <driverlib.h>
#include "clock.h"
#include "gpio.h"
#include <stdio.h>

/*
 * main.c
 */

void doStuff();

unsigned int i = 0;


int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    gpio_init();
    printf("init test \n");
    while(1){
        doStuff();
    }
	return 0;
}


void
outPut()
{
    //for (i=0;i<8;i++){
        GPIO_toggleOutputOnPin(gpio_PORT_P6, gpio_PIN6);
        //__delay_cycles(1U);
        GPIO_toggleOutputOnPin(gpio_PORT_P6, gpio_PIN6);
       // __delay_cycles(1U);
        GPIO_toggleOutputOnPin(gpio_PORT_P6, gpio_PIN6);
       // __delay_cycles(1U);
        GPIO_toggleOutputOnPin(gpio_PORT_P6, gpio_PIN6);
       // __delay_cycles(1U);
        GPIO_toggleOutputOnPin(gpio_PORT_P6, gpio_PIN6);
       // __delay_cycles(1U);
        GPIO_toggleOutputOnPin(gpio_PORT_P6, gpio_PIN6);
       // __delay_cycles(1U);
        GPIO_toggleOutputOnPin(gpio_PORT_P6, gpio_PIN6);
       // __delay_cycles(1U);
        GPIO_toggleOutputOnPin(gpio_PORT_P6, gpio_PORT_P6);
   // }
}


void
doStuff()
{
    if(! gpio_getPinInput(gpio_PORT_P1, gpio_PIN1))
    {
        printf("btn press \n");
        gpio_setPinHigh(gpio_PORT_P3, gpio_PIN2);
        outPut();
        gpio_setPinLow(gpio_PORT_P3, gpio_PIN2);
    }
    else{
    gpio_setPinLow(gpio_PORT_P3, gpio_PIN2);
    printf("no btn press \n");
    }
    __delay_cycles(10000U);

}
