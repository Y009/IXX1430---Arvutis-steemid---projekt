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

int row;
int column;
unsigned int newData;
unsigned int element;
unsigned int i;
unsigned int j;
unsigned int lastBufferPos;         /* Used to indicate what point in matrix to display */
unsigned int data [SIZEOFMATR][SIZEOFMATR];
unsigned int rawData [SIZEOFRAWMATR2][SIZEOFRAWMATR];



void
shiftreg_init()
{
    //clearing all matrices
    i = 0;
    j = 0;
    newData = FALSE;
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
    if (newData)
        convertMatr();

        if(lastBufferPos == 0)
        {
            lastBufferPos = SIZEOFMATR;
            clearRowData();
        }
        outputBuffer(lastBufferPos);
        shiftThroughRows();
        lastBufferPos--;
//    }
}

void
clearRowData()
/*
 * clearing all row data causing all leds to go to OFF state
 * and be ready for new data to be displayed.
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
    }

    en_shiftreg1();
    en_shiftreg2();
    dis_shiftreg1();
    dis_shiftreg2();
    en_output();
}

void
outputBuffer(unsigned int bufferPos)
/*
 * Sends the current column value of the data matrix to the shiftregisters, based on the bufferPos index.
 *
 */
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
/*
 * As the higher level operates with a matrix with the size of 14x10
 * it is necessary to convert it to a 16x16 matrix because the shiftregisters have 8 outputs
 * and this function skips over the rows and columns that do not get displayed on the physical LEDs.
 *
 */
{
    int column = 0 ;                        // helping variables to allow conversion between matrices
    int row = 0;

    for (i = 0 ; i < SIZEOFRAWMATR2; i++)
    {
        if (i == (SIZEOFRAWMATR2 / 2))
            row = row + 4;                  // increment + number of unused rows
        else if (i == 0 )
            ;
        else
            row++;

        for (j = 0 ; j < SIZEOFRAWMATR; j++)
        {
            if (j == (SIZEOFRAWMATR / 2))
                column = column + 2;        // increment + number of unused columns
            else
                column++;
            if (rawData[i][j])
                data [row][column] = TRUE;
            else
                data [row][column] = FALSE;
        }
        column = 0;
    }
    newData = FALSE;
}

void
shiftreg_set_newMatr(unsigned int transfer [SIZEOFRAWMATR2][SIZEOFRAWMATR])
/*
 * Public function to allow LED controller to give data about what to display.
 */
{
    for(i = 0; i < SIZEOFRAWMATR2; i++)
    {
        for(j = 0; j < SIZEOFRAWMATR; j++)
        {
            rawData[i][j] = transfer[i][j];
        }
    }
    newData = TRUE;
}


/*
 * Following functions are GPIO related
 * and are used to give data to shiftregisters.
 */
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
    gpio_setPinHigh(gpio_PORT_P2, gpio_PIN4);
}

void
clockDwn()
{
    gpio_setPinLow(gpio_PORT_P2, gpio_PIN4);
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
