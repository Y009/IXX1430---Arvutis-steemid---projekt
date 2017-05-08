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
#include "shiftreg.h"
#include "stdio.h"
#include "timer.h"

#define TRUE 1
#define FALSE 0

#define UP 4
#define DOWN 3
#define RIGHT 2
#define LEFT 1
#define NOTMOVING 0

#define PLATFORM1 11
#define PLATFORM2 12
#define PLATFORM3 13
#define PLATFORM4 14
#define BALL 5
#define BLOCK 1
#define BLOCK2 2
#define EMPTY 0

#define BALLDIR1 1
#define BALLDIR2 2
#define BALLDIR3 3
#define BALLDIR4 4
#define BALLDIR5 7
#define BALLDIR6 8
#define BALLDIR7 12


void logic_movePlatform();
void movePlatform(unsigned int dir);



unsigned int playField [SIZEOFRAWMATR2][SIZEOFRAWMATR] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 11,12,13,14,0, 0, 0, 0, 0}
};

unsigned int ballDir;
unsigned short int ballDirUp;   // ball moving upwards == TRUE;
unsigned upCounter;             // how much the ball has moved up/down. Used in move_dir functions to know how to move..
unsigned int platformStatus;    // shows if the platform is in motion. if so then which way
unsigned int i;                 // used for loops
unsigned long long int delay = 100;
unsigned long long int lastCounter = 0;
unsigned long long int test = 0;
unsigned int ballPos1;
unsigned int ballPos2;


void
logic_init()
/**
 * 1st time setup
 *
 */
{
    ballPos1 = 8;   // on what row
    ballPos2 = 7;   // on what column
    ballDir = BALLDIR5;
    ballDirUp = TRUE;
    platformStatus = NOTMOVING;
    shiftreg_set_newMatr(playField);

}

void
logic_cyclic()
/**
 * get input, act on it
 * see gamelogic.png
 *
 */
{
    test = timer_getCounter();
    if(timer_getCounter() - lastCounter >= delay)             // delay with timer to make the game playable
    {
        logic_movePlatform();
        lastCounter = timer_getCounter();

    }
}

void
logic_movePlatform()
/**
 * move platform based on input from buttons
 * check if touching wall
 */
{
    if (! GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN1))                               // move left
    {
        if ( (playField[SIZEOFRAWMATR2 - 1][0])  != PLATFORM1)                          // check last rows 1st element
        {
            platformStatus = LEFT;
            movePlatform(platformStatus);
        }
    }
    else if (! GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1))                          // move right
    {
        if ( (playField[SIZEOFRAWMATR2 - 1][ SIZEOFRAWMATR - 1])  != PLATFORM4)         // check last rows last element
        {
            platformStatus = RIGHT;
            movePlatform(platformStatus);
        }
    }
    else if ( (! GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN1)) && (! GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1)))
        platformStatus = NOTMOVING;
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
    //shiftreg_set_newMatr(playField);
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
    return 0;
}

int
logic_checkCollionAngle()
/**
 * if checkCollison returned 1, 2 or 3
 * check at what angle it hit it and give the ball a new move dir
 * returns new angle
 */
{
    return 0;
}

void
logic_updateLED()
/**
 * send game board to led module to be displayed
 */
{
    shiftreg_set_newMatr(playField);
}


void
movePlatform(unsigned int dir)
{
    if (dir == RIGHT)
    {
        for ( i = 3 ; i < SIZEOFRAWMATR ; i++)      /* find the right edge of the platform and move the platform
                                                    i = 3 to optimize; because the right farthest platform
                                                    element can never be at index less than 3.
                                                    */
        {
            if (playField[SIZEOFRAWMATR2 - 1][i] == PLATFORM4)
            {
                playField[ SIZEOFRAWMATR2 - 1 ][ i + 1 ] = playField[ SIZEOFRAWMATR2 - 1 ][ i ];
                playField[ SIZEOFRAWMATR2 - 1 ][ i ]     = playField[ SIZEOFRAWMATR2 - 1 ][ i - 1];
                playField[ SIZEOFRAWMATR2 - 1 ][ i - 1 ] = playField[ SIZEOFRAWMATR2 - 1 ][ i - 2 ];
                playField[ SIZEOFRAWMATR2 - 1 ][ i - 2 ] = playField[ SIZEOFRAWMATR2 - 1 ][ i - 3 ];
                playField[ SIZEOFRAWMATR2 - 1 ][ i - 3 ] = 0;
                break;
            }
        }

    }
    else if (dir  == LEFT)                              // as else if just in case it gets here through some error.
    {
        for ( i = 0 ; i < SIZEOFRAWMATR ; i++)  /* find the left edge of the platform and move the platform
                                                    SIZEOFRAWMATR -4  to optimize; because the left farthest platform
                                                    element can never be at index more then than 10.
                                                    */
        {
            if (playField[SIZEOFRAWMATR2 - 1][i] == PLATFORM1)
            {
                playField[ SIZEOFRAWMATR2 - 1 ][ i - 1 ] = playField[ SIZEOFRAWMATR2 - 1 ][ i ];
                playField[ SIZEOFRAWMATR2 - 1 ][ i ]     = playField[ SIZEOFRAWMATR2 - 1 ][ i + 1];
                playField[ SIZEOFRAWMATR2 - 1 ][ i + 1 ] = playField[ SIZEOFRAWMATR2 - 1 ][ i + 2 ];
                playField[ SIZEOFRAWMATR2 - 1 ][ i + 2 ] = playField[ SIZEOFRAWMATR2 - 1 ][ i + 3 ];
                playField[ SIZEOFRAWMATR2 - 1 ][ i +3 ] = 0;
                break;
            }
        }
    }

    logic_updateLED();

}

void
removeBlock(unsigned int row, unsigned int col)
{
    playField[row][col]--;
}

int
checkpos(unsigned int dir)
{
    if (dir == UP)
    {
        if(playField[ ballPos1 - 1][ ballPos2 ] == EMPTY)
            return 1;
        else if ( playField[ ballPos1 - 1 ][ ballPos2] == BLOCK )
        {
            removeBlock(ballPos1 - 1, ballPos2);
            changeDir();
            ballDirUP = FALSE;
            return 0;
        }
        else if (ballPos1 - 1 < 0)                               // outer wall
        {
            changeDir();
            ballDirUP = FALSE;
            return 0;
        }

    }
    else if (dir == DOWN)
    {
        if(playField[ ballPos1 + 1][ ballPos2 ] == EMPTY)
            return 1;
        else if ( playField[ ballPos1 - 1 ][ ballPos2] == BLOCK )
        {
            removeBlock(ballPos1 + 1, ballPos2);
            ballDirUP = TRUE;
            changeDir();
            return 0;
        }
        else if (playField[ ballPos1 + 1][ ballPos2 ] == PLATFORM1 ||
                 playField[ ballPos1 + 1][ ballPos2 ] == PLATFORM2 ||
                 playField[ ballPos1 + 1][ ballPos2 ] == PLATFORM3 ||
                 playField[ ballPos1 + 1][ ballPos2 ] == PLATFORM4  )
        {
            ballDirUP = TRUE;
            changeDir();
            return 0;
        }
        else if (ballPos1 - 1 < 0)                               // out of bounds
            ; // fucking noob failed.
              //!TODO write function for failure...
    }

    else if (dir == RIGHT)
    {
        if(playField[ ballPos1][ ballPos2 +1 ] == EMPTY)
            return 1;
        else if (ballPos2 + 1 < 0)                               // outer wall
        {
            changeDir();
            return 0;
        }
    }

    else if (dir == LEFT)
    {
        if(playField[ ballPos1][ ballPos2 -1] == EMPTY)
            return 1;
        else if (ballPos2 - 1 < 0)                               // outer wall
        {
            changeDir();
            return 0;
        }
    }
    return 0;
}

//
void
move_dir1
{
    if(ballDirUp == TRUE )
    {
        if(checkPos(UPLEFT))
        {
            move_ball_upleft();
        }
    }
    else
    {
        if(checkPos(UPLEFT))
        {
            move_ball_downleft();
        }
    }
}
//
void
move_dir2
{
    if(balldirUp == TRUE)
    {
        if((upCounter == 0))
        {
            if(checkPos(UPLEFT))
            {
                move_ball_upleft();
            }
        }
        else
        {
            if(checkPos(UP))
            {
                move_ball_up();
            }
        }
    }
    else
    {
        if((upCounter == 0))
        {
            if(checkPos(DOWNLEFT))
            {
                move_ball_downleft();
            }
        }
        else
        {
            if(checkPos(DOWN))
            {
                move_ball_down();
            }
        }
    }
    upCounter++;
    if(upCounter == 3)
        upCounter = 0;
}

void
move_dir3
{
    if(balldirUp == TRUE)
    {
        if((upCounter == 3))
        {
            if(checkPos(UPLEFT))
            {
                move_ball_upleft();
                upCounter = 0;
            }
        }
        else
        {
            if(checkPos(UP))
            {
                move_ball_up();
            }
        }
    }
    else
    {
        if((upCounter == 3))
        {
            if(checkPos(DOWNLEFT))
            {
                move_ball_downleft();
                upCounter = 0;
            }
        }
        else
        {
            if(checkPos(DOWN))
            {
                move_ball_down();
            }
        }
    }
    upCounter++;
}

void
move_dir4
{
    if(ballDirUp == TRUE )
    {
        if(checkPos(UP))
        {
            move_ball_up();
        }
    }
    else
    {
        if(checkPos(UP))
        {
            move_ball_down();
        }
    }
}

void
move_dir5
{
    if(balldirUp == TRUE)
     {
         if((upCounter == 3))
         {
             if(checkPos(UPRIGHT))
             {
                 move_ball_upright();
                 upCounter = 0;
             }
         }
         else
         {
             if(checkPos(UP))
             {
                 move_ball_up();
             }
         }
     }
     else
     {
         if((upCounter == 3))
         {
             if(checkPos(DOWNRIGHT))
             {
                 move_ball_downright();
                 upCounter = 0;
             }
         }
         else
         {
             if(checkPos(DOWN))
             {
                 move_ball_down();
             }
         }
     }
     upCounter++;
}

void
move_dir6
{
    if(balldirUp == TRUE)
    {
        if((upCounter == 0))
        {
            if(checkPos(UPRIGHT))
            {
                move_ball_upright();
            }
        }
        else
        {
            if(checkPos(UP))
            {
                move_ball_up();
            }
        }
    }
    else
    {
        if((upCounter == 0))
        {
            if(checkPos(DOWNRIGHT))
            {
                move_ball_downright();
            }
        }
        else
        {
            if(checkPos(DOWN))
            {
                move_ball_down();
            }
        }
    }
    upCounter++;
    if(upCounter == 3)
        upCounter = 0;
}

void
move_dir7
{
    if(ballDirUp == TRUE )
    {
        if(checkPos(UPRIGHT))
        {
            move_ball_upright();
        }
    }
    else
    {
        if(checkPos(UPRIGHT))
        {
            move_ball_downright();
        }
    }
}

void
move_ball_downright()
{
    move_ball_remove();
    ballPos1++;
    ballPos2++;
    move_ball_reAdd();
}

void
move_ball_downleft()
{
    move_ball_remove();
    ballPos1++;
    ballPos2--;
    move_ball_reAdd();
}

void
move_ball_downright()
{
    move_ball_remove();
    ballPos1++;
    move_ball_reAdd();
}

void
move_ball_upright()
{
    move_ball_remove();
    ballPos1--;
    ballPos2++;
    move_ball_reAdd();
}

void
move_ball_upleft()
{
    move_ball_remove();
    ballPos1--;
    ballPos2--;
    move_ball_reAdd();
}

void
move_ball_up()
{
    move_ball_remove();
    ballPos1--;
    move_ball_reAdd();
}

void
move_ball_remove()
{
    playField[ballPos1][Ballpos2] = EMPTY;
}

void
move_ball_reAdd()
{
    playField[ballPos1][Ballpos2] = BALL;
}






