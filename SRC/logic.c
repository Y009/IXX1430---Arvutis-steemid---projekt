/*
 * logic.c
 *
 *  Created on: 18 Apr 2017
 *      Author: Y009
 *      !TODO! Write functions.
 */


//***** Header Files **********************************************************
#include <driverlib.h>
#include "logic.h"

void
logic_init()
/**
 * 1st time setup
 * choose board, set values to start
 */{
}

void
logic_cyclic()
/**
 * get input, act on it
 * see gamelogic.png
 *
 */
{
}

void
logic_movePlatform()
/**
 * move platform based on input from buttons
 * check if touching wall
 */
{
}

void
logic_moveBall()
/**
 * move ball based on move dir
 * check if touching anything
 */
{
}

void
logic_updateBlocks()
/**
 * update blocks when something gets changed
 */
{
}

int
logic_checkCollison()
/**
 * check balls collison with anything
 * ret 0 - nothing
 * ret 1 - platform
 * ret 2 - block
 * ret 3 - wall
 * ret 4 - out of bound (player didnt catch ball)
 */
{
}

int
logic_checkCollionAngle()
/**
 * if checkCollison returned 1, 2 or 3
 * check at what angle it hit it and give the ball a new move dir
 * returns new angle
 */
{
}

void
logic_updateLED()
/**
 * send game board to led module to be displayed
 */
{
}

int
logic_getInput()
/**
 * get input from buttons
 * ret 0 - no input
 * ret 1 - left
 * ret 2 - right
 */
{
}















