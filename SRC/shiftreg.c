/*
 * shiftreg.c
 *
 *  Created on: 2. mai 2017
 *      Author: Y009
 */

#include <driverlib.h>
#include "shiftreg.h"
#include "gpio.h"
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define SIZEOFMATR 16
#define SIZEOFRAWMATR 14
#define SIZEOFRAWMATR2 10
#define STARTPOS

//test matrices
/*
unsigned int data [SIZEOFMATR][SIZEOFMATR] = {
      {0, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1},//0
      {0, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1},
      {0, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1},
      {0, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1},
      {0, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1},

      {0, 0,0,0,0,0,0,0, 0, 0,0,0,0,0,0,0},
      {0, 0,0,0,0,0,0,0, 0, 0,0,0,0,0,0,0},
      {0, 0,0,0,0,0,0,0, 0, 0,0,0,0,0,0,0}, //7

      {0, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1},
      {0, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1},
      {0, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1},
      {1, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1},
      {1, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1},

      {1, 1,1,0,0,0,0,1, 0, 1,1,1,0,0,0,0}, //5,6,7,13,14,15, on fyysiliselt v2lja j22vad read
      {1, 0,0,1,1,0,0,1, 0, 1,0,0,1,0,1,0},
      {0, 1,0,1,0,1,0,1, 1, 0,1,0,1,1,0,1}  //15
};  // col 1,8 j22b samuti v2lja
*/

unsigned int data [SIZEOFMATR][SIZEOFMATR] = {
      {0, 0,0,0,0,1,0,0, 0, 0,0,0,0,0,0,1}, //0
      {0, 0,0,0,1,0,1,0, 0, 0,0,0,0,0,1,0},
      {0, 0,0,1,0,0,0,1, 0, 1,0,0,0,1,0,0},
      {0, 0,1,0,0,0,0,0, 0, 0,1,0,1,0,0,0},
      {0, 1,0,0,0,0,0,0, 0, 0,0,1,0,0,0,1},

      {0, 0,0,0,0,0,0,0, 0, 0,0,0,0,0,0,0},
      {0, 0,0,0,0,0,0,0, 0, 0,0,0,0,0,0,0},
      {0, 0,0,0,0,0,0,0, 0, 0,0,0,0,0,0,0}, //7

      {0, 0,0,0,0,1,0,0, 0, 0,0,0,0,0,0,1},
      {0, 0,0,0,1,0,1,0, 0, 0,0,0,0,0,1,0},
      {0, 0,0,1,0,0,0,1, 0, 1,0,0,0,1,0,0},
      {0, 0,1,0,0,0,0,0, 0, 0,1,0,1,0,0,0},
      {1, 1,0,0,0,0,0,0, 0, 0,0,1,0,0,0,1},

      {1, 1,1,0,0,0,0,1, 0, 1,1,1,0,0,0,0}, //5,6,7,13,14,15, on fyysiliselt v2lja j22vad read
      {1, 0,0,1,1,0,0,1, 0, 1,0,0,1,0,1,0},
      {0, 1,0,1,0,1,0,1, 1, 0,1,0,1,1,0,1}  //15
};  // col 1,8 j22b samuti v2lja
/*
unsigned int data [SIZEOFMATR][SIZEOFMATR] = {
      {0, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1},//0
      {0, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1},
      {0, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1},
      {0, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1},
      {0, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1},

      {0, 0,0,0,0,0,0,0, 0, 0,0,0,0,0,0,0},
      {0, 0,0,0,0,0,0,0, 0, 0,0,0,0,0,0,0},
      {0, 0,0,0,0,0,0,0, 0, 0,0,0,0,0,0,0}, //7

      {0, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1},
      {0, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1},
      {0, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1},
      {1, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1},
      {1, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1},

      {1, 1,1,0,0,0,0,1, 0, 1,1,1,0,0,0,0}, //5,6,7,13,14,15, on fyysiliselt v2lja j22vad read
      {1, 0,0,1,1,0,0,1, 0, 1,0,0,1,0,1,0},
      {0, 1,0,1,0,1,0,1, 1, 0,1,0,1,1,0,1}  //15
};  // col 1,8 j22b samuti v2lja
*/

//rawData from LED controller to be converted to a usable format for shiftregister (16x16)
unsigned int rawData [SIZEOFRAWMATR2][SIZEOFRAWMATR] = {
    {0,1,1,1,1,1,0, 0,0,1,0,1,1,0},
    {0,0,1,1,1,0,0, 0,0,1,1,1,0,0},
    {0,0,0,1,1,0,1, 0,1,0,0,0,1,0},
    {0,0,0,0,1,0,0, 1,0,0,0,0,0,1},
    {1,1,1,1,1,1,1, 0,0,0,0,0,0,0},

    {0,1,1,1,1,0,1, 0,0,1,0,1,1,0},
    {1,0,1,0,1,0,1, 1,0,0,0,0,1,1},
    {0,0,0,0,1,0,1, 0,0,1,0,0,1,0},
    {0,0,0,0,1,0,1, 1,0,1,0,0,1,1},
    {1,1,1,0,1,0,1, 0,0,1,1,0,1,0}
};

int row;
int column;
unsigned int element;
unsigned int i = 0;
unsigned int j = 0;
unsigned int lastBufferPos;         /* Used to indicate what point in matrix to display */
//unsigned int data [SIZEOFMATR][SIZEOFMATR];
//unsigned int rawData [][];

void clearRowData();
void shiftThroughRows();
void outputBuffer(unsigned int bufferPos);
void convertMatr();
void outputRow();
void outputRowNull();
void outputColNull();
void outputCol();
void rowDataHi();
void rowDataLow();
void colDataHi();
void colDataLow();
void clockUp();
void clockDwn();
void en_shiftreg1();
void dis_shiftreg1();
void en_shiftreg2();
void dis_shiftreg2();
void en_shiftreg3();
void dis_shiftreg3();
void en_shiftreg4();
void dis_shiftreg4();
void en_output();
void dis_output();

void shiftreg_init()
{
    //clearing all matrices
    gpio_init();
    clearRowData();
    en_shiftreg1();
    en_shiftreg2();
    en_shiftreg3();
    en_shiftreg4();

    dis_shiftreg1();
    dis_shiftreg2();
    dis_shiftreg3();
    dis_shiftreg4();

    en_output();
}


void
shiftreg_exec()
{
    if (! GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN1))
    {
        /*
        en_shiftreg1();
        en_shiftreg2();
        outputRow();
        dis_shiftreg1();
        dis_shiftreg2();
        */
        printf("\n");
        for (i = 0 ; i < SIZEOFRAWMATR2 ; i++)
        {
            for(j = 0 ; j < SIZEOFRAWMATR ; j++)
            {
                printf("%d ", rawData [i][j]);
            }
            printf("\n");
        }
        printf("new matr \n");
        printf("\n");
        convertMatr();
        for (i = 0 ; i < SIZEOFMATR ; i++)
        {
            for(j = 0 ; j < SIZEOFMATR ; j++)
            {
                printf("%d ", data [i][j]);
            }
            printf("\n");
        }
    }

    if (! GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1))
    {
        if(lastBufferPos == 0)
        {
            lastBufferPos = SIZEOFMATR;
            clearRowData();
        }
        outputBuffer(lastBufferPos);
        shiftThroughRows();
        lastBufferPos--;
    }
}

void
clearRowData()
/*
 * clearing all row data causing all leds to go to OFF state
 */
{
    for(i = 0; i < SIZEOFMATR;  i++)
    {
       outputRowNull();
    }
}

void
shiftThroughRows()
/*
 *
 */
{
    dis_output();
    en_shiftreg3();
    en_shiftreg4();
    dis_shiftreg3();
    dis_shiftreg4();

    dis_shiftreg1();
    dis_shiftreg2();
    outputRow();

    for(i = (SIZEOFMATR - lastBufferPos); i > 0;  i--)
    {
       outputRowNull();
       //__delay_cycles(100000U);
    }

    en_shiftreg1();
    en_shiftreg2();
    dis_shiftreg1();
    dis_shiftreg2();
    en_output();
}

void
outputBuffer(unsigned int bufferPos)
{
    for (row = SIZEOFMATR-1;row >= 0; row--)
    {

        if (data[row][bufferPos-1] == TRUE)
            outputCol();
        else
            outputColNull();
    }
}


void
convertMatr()
{
    int veerg = 0 ; // helping variables to allow conversion between matrices
    int rida = 0;

    for (i = 0 ; i < SIZEOFRAWMATR2; i++)
    {
        if (i == (SIZEOFRAWMATR2 / 2))
            rida = rida + 4; // increment + number of unused rows
        else if (i == 0 )
            ;
        else
            rida = rida + 1;

        for (j = 0 ; j < SIZEOFRAWMATR; j++)
        {
            if (j == (SIZEOFRAWMATR / 2))
                veerg = veerg + 2; // increment + number of unused columns
                veerg = veerg + 1;
            data [rida][veerg] = rawData[i][j];
        }
        veerg = 0;
    }
}



void
outputRow()
{
    rowDataHi();
    clockUp();
    clockDwn();
    rowDataLow();
}

void
outputRowNull()
{
    rowDataLow();
    clockUp();
    clockDwn();
}

void
outputColNull()
{
    colDataHi();
    clockUp();
    clockDwn();
    colDataLow();
}

void
outputCol()
{
    colDataLow();
    clockUp();
    clockDwn();
}

void
rowDataHi()
{
    gpio_setPinHigh(gpio_PORT_P6, gpio_PIN6);
}

void
rowDataLow()
{
    gpio_setPinLow(gpio_PORT_P6, gpio_PIN6);
}

void
colDataHi()
{
    gpio_setPinHigh(gpio_PORT_P6, gpio_PIN3);
}

void
colDataLow()
{
    gpio_setPinLow(gpio_PORT_P6, gpio_PIN3);
}

void
clockUp()
{
    gpio_setPinHigh(gpio_PORT_P2, gpio_PIN2);
}

void
clockDwn()
{
    gpio_setPinLow(gpio_PORT_P2, gpio_PIN2);
}

void
en_shiftreg1()
{
    gpio_setPinHigh(gpio_PORT_P3, gpio_PIN2);
}
void
dis_shiftreg1()
{
    gpio_setPinLow(gpio_PORT_P3, gpio_PIN2);
}

void
en_shiftreg2()
{
    gpio_setPinHigh(gpio_PORT_P3, gpio_PIN3);
}
void
dis_shiftreg2()
{
    gpio_setPinLow(gpio_PORT_P3, gpio_PIN3);
}

void
en_shiftreg3()
{
    gpio_setPinHigh(gpio_PORT_P3, gpio_PIN0);
}

void
dis_shiftreg3()
{
    gpio_setPinLow(gpio_PORT_P3, gpio_PIN0);
}

void
en_shiftreg4()
{
    gpio_setPinHigh(gpio_PORT_P3, gpio_PIN1);
}

void
dis_shiftreg4()
{
    gpio_setPinLow(gpio_PORT_P3, gpio_PIN1);
}

void
en_output()
{
    gpio_setPinHigh(gpio_PORT_P3, gpio_PIN4);
}

void
dis_output()
{
    gpio_setPinLow(gpio_PORT_P3, gpio_PIN4);
}

