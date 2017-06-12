/*
 * logic.c
 *
 *  Created on: 18 Apr 2017
 *      Author: Y009
 */


//***** Header Files **********************************************************
#include <driverlib.h>
#include "logic.h"
#include "shiftreg.h"
#include "timer.h"

#define TRUE 1
#define FALSE 0

#define DOWNLEFT 8
#define DOWNRIGHT 7
#define UPLEFT 6
#define UPRIGHT 5
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

#define gameResetTime 10000000        /* Changing this modifies the delay before
                                     * automatically starting a new game
                                     *
                                     * !Can still be optimized!
                                     */
#define gameTimeModifier 25000      /* This value controls the conversion of the timer's
                                     * value to a suitable score value.
                                     *
                                     * !Can still be optimized!
                                     */
void logic_updateLED();
void logic_movePlatform();
void movePlatform(unsigned int dir);
void logic_moveBall();
void move_dir1();
void move_dir2();
void move_dir3();
void move_dir4();
void move_dir5();
void move_dir6();
void move_dir7();
void move_ball_upright();
void move_ball_upleft();
void move_ball_up();
void move_ball_downright();
void move_ball_downleft();
void move_ball_down();
void move_ball_upright();
void move_ball_remove();
void move_ball_reAdd();
void changeDir();
int checkpos(unsigned int moveDir);
void convertTime();
void missPlatform();
char checkLastRow();
void copyPlayField();


//Default starting playField
/*
unsigned int defaultPlayField [SIZEOFRAWMATR2][SIZEOFRAWMATR] = {
    {0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 11,12,13,14,0, 0, 0, 0, 0}
};
*/
unsigned int defaultPlayField [SIZEOFRAWMATR2][SIZEOFRAWMATR] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 11,12,13,14,0, 0, 0, 0, 0}
};

unsigned int playField [SIZEOFRAWMATR2][SIZEOFRAWMATR];
unsigned int ballDir;
unsigned short int ballDirUp;           // ball moving upwards == TRUE;
unsigned upCounter;                     // how much the ball has moved up/down. Used in move_dir functions to know how to move..
unsigned int platformStatus;            // shows if the platform is in motion. if so then which way
unsigned int i;                         // used for loops
unsigned int j;                         // used for loops
unsigned long long int delay;           // delay for ball's movement
unsigned long long int delay2;          // delay for platform's movement
unsigned long long int lastCounter;     // delaycounter for ball's movement
unsigned long long int lastCounter2;    // delaycounter for platform's movement
unsigned long long int gameTime;        // elapsed game time
unsigned long long int gameTime2;       // difference between game end time and current time
unsigned int gameOver;                  // gameover status
unsigned int gameWon;                   // gamewin status
unsigned int gameOverStatusSet;         // to disable work with gameOver if time has been set
unsigned int lives;                     // amount of lives the player gets (number of balls to clear the matrix)
unsigned int platformHit;               // the specific block that the ball hit the platform on
unsigned int blockCount;                // number of blocks on the playfield

// 3d array to store scores for easy access
unsigned int scoreNumbers[10][SIZEOFRAWMATR2][SIZEOFRAWMATR /2 ] = {LED0, LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9};

int ballPos1;                           // tracking the ball's position; has to be signed for position check
int ballPos2;                           // tracking the ball's position; has to be signed for position check

unsigned long long int test = 0;

void
logic_init()
/**
 * Setup
 */
{
    copyPlayField();
    ballPos1 = 7;   // on what row
    ballPos2 = 8;   // on what column   based on default playfield to ease control
    blockCount = 56;

    ballDir = BALLDIR4;
    ballDirUp = TRUE;
    platformStatus = NOTMOVING;
    shiftreg_set_newMatr(playField);

    gameOver = FALSE;
    gameWon = FALSE;
    gameOverStatusSet = FALSE;
    lives = 2;

    delay = 3000;
    delay2 = 1000;
    lastCounter = 0;
    lastCounter2 = 0;

    set_timerCounter();

    timer_init();

}


void
logic_cyclic()
/**
 * Get input, act on it
 * see gamelogic.png
 */
{
    if( (timer_getCounter() - lastCounter >= delay ) && (!gameOver) && (!gameWon) )               // delay with timer to make the game playable
    {
        logic_moveBall();
        lastCounter = timer_getCounter();
    }

    if(gameWon == TRUE)
    {
        if ( gameOverStatusSet == TRUE)
        {
            ;
        }
        else
        {
            gameTime = timer_getCounter();
            gameOverStatusSet = TRUE;
            convertTime();
            logic_updateLED();
        }
    }
    else if(gameOver == TRUE)
    {
        logic_init();                           // Reinitialize the game
    }

    if( (timer_getCounter() - lastCounter2 >= delay2 ) && !gameOver)             // delay with timer to make the game playable
    {
        logic_movePlatform();
        lastCounter2 = timer_getCounter();

    }
}

void
copyPlayField()
{
    for (i = 0 ; i < SIZEOFRAWMATR2; i++)
    {
        for (j = 0 ; j < SIZEOFRAWMATR; j++)
        {
            playField[i][j] = defaultPlayField[i][j];
        }
    }
}

void
/*
 * Convert's the timer's value to usable number.
 * Time is reduced to a value between 0-99.
 * To keep the score easily displayable.
 * Set's the game score/time on the playField matrix
 */
convertTime()
{
    int number = ((gameTime / gameTimeModifier)/10) % 10 ;
    int number2 = (gameTime / gameTimeModifier) % 10;

    // Setting the left number
    for(i = 0; i < SIZEOFRAWMATR2 ; i++)
    {
        for(j = 0; j < SIZEOFRAWMATR / 2; j++)
        {

                playField[i][j] = scoreNumbers[number][i][j];

        }
    }

    // Setting the right number
    for(i = 0; i < SIZEOFRAWMATR2 ; i++)
    {
        for(j = SIZEOFRAWMATR / 2; j < SIZEOFRAWMATR; j++)                     // continuing from the right side of the matrix
        {
            playField[i][j] = scoreNumbers[number2][i][j - SIZEOFRAWMATR / 2]; // Number matrix's value has to be balanced back
        }

    }

}

void
logic_movePlatform()
/**
 * Move platform based on input from buttons
 * Check if touching wall
 */
{
    if (! GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN1))                               // move left
    {
        if ( ((playField[SIZEOFRAWMATR2 - 1][0])  != PLATFORM1)  && checkLastRow())                          // check last rows 1st element
        {
            platformStatus = LEFT;
            movePlatform(platformStatus);
        }
    }
    else if (! GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1))                          // move right
    {
        if ( ( (playField[SIZEOFRAWMATR2 - 1][ SIZEOFRAWMATR - 1])  != PLATFORM4) && checkLastRow() )         // check last rows last element
        {
            platformStatus = RIGHT;
            movePlatform(platformStatus);
        }
    }
    else
    {
        platformStatus = NOTMOVING;
    }
}

char
/*
 * Checks last row for ball
 */
checkLastRow()
{

    if( (ballPos1 + 1) == SIZEOFRAWMATR2)
        return FALSE;

    return TRUE;
}

void
/*
 * Ball's direction change from blocks and walls.
 */
changeDir()
{
    switch (ballDir)
    {
    case BALLDIR1:
        ballDir = BALLDIR7;
        break;

    case BALLDIR2:
        ballDir = BALLDIR6;
        break;

    case BALLDIR3:
        ballDir = BALLDIR5;
        break;

    case BALLDIR4:
        // stays dir4 because the ball's moving straight up/down
        break;

    case BALLDIR5:
        ballDir = BALLDIR3;
        break;

    case BALLDIR6:
        ballDir = BALLDIR2;
        break;

    case BALLDIR7:
        ballDir = BALLDIR1;
        break;
    }
    upCounter = 0;      // reset upcounter to ensure movement in new direction to be accurate
}

void
/*
 * Ball's direction change according to where it hit the platform
 * and whether the platform was moving or not.
 */
changeDir_Platform()
{
    ballDirUp = TRUE;

    if (platformStatus == LEFT)
    {
        switch (platformHit)
        {
        case PLATFORM1:
            ballDir = BALLDIR4;
            break;

        case PLATFORM2:
            ballDir = BALLDIR5;
            break;

        case PLATFORM3:
            ballDir = BALLDIR6;
            break;

        case PLATFORM4:
            ballDir = BALLDIR7;
            break;
        }
    }

    else if (platformStatus == RIGHT)
    {
        switch (platformHit)
        {
        case PLATFORM1:
            ballDir = BALLDIR1;
            break;

        case PLATFORM2:
            ballDir = BALLDIR2;
            break;

        case PLATFORM3:
            ballDir = BALLDIR3;
            break;

        case PLATFORM4:
            ballDir = BALLDIR4;
            break;
        }
    }

    else if (platformStatus == NOTMOVING)
    {
        switch (platformHit)
        {
        case PLATFORM1:
            ballDir = BALLDIR2;
            break;

        case PLATFORM2:
            ballDir = BALLDIR3;
            break;

        case PLATFORM3:
            ballDir = BALLDIR5;
            break;

        case PLATFORM4:
            ballDir = BALLDIR6;
            break;
        }
    }
    upCounter = 0;      // reset upcounter to ensure movement in new direction to be accurate
}


void
logic_moveBall()
/**
 * move ball based on move dir
 * check if touching anything
 */
{
    switch (ballDir)
    {
    case BALLDIR1:
        move_dir1();
        break;

    case BALLDIR2:
        move_dir2();
        break;

    case BALLDIR3:
        move_dir3();
        break;

    case BALLDIR4:
        move_dir4();
        break;

    case BALLDIR5:
        move_dir5();
        break;

    case BALLDIR6:
        move_dir6();
        break;

    case BALLDIR7:
        move_dir7();
        break;
    }
    logic_updateLED();
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
/*
 * Platform movement on the last row of the playfield
 * movement is restricted strictly to that rows elements
 */
movePlatform(unsigned int dir)
{
    if (dir == RIGHT)
    {
        for ( i = 3 ; i < SIZEOFRAWMATR ; i++)      /* find the right edge of the platform and move the platform
                                                     * i = 3 to optimize; because the right farthest platform
                                                     * element can never be at index less than 3.
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
    else if (dir  == LEFT)
    {
        for ( i = 0 ; i < SIZEOFRAWMATR ; i++)      /* find the left edge of the platform and move the platform
                                                     * SIZEOFRAWMATR -4  to optimize; because the left farthest platform
                                                     * element can never be at index more then than 10.
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
/*
 * Ball misses the platform
 * Check for lives.
 * REinit ball if needed
 */
missPlatform()
{
    if(lives > 0)
    {                   // reinitialize ball
        move_ball_remove();
        ballPos1 = 8;
        ballPos2 = 7;
        ballDirUp = TRUE;
        playField [ballPos1][ballPos2] = BALL;
        lives--;
    }
    else
    {
        gameOver = TRUE;
    }
}


void
removeBlock(unsigned int row, unsigned int col)
{
    playField[row][col]--;
    blockCount--;
    if(blockCount == 0)
    {
        gameWon = TRUE;
    }
}

int
/*
 * Based on ball's movement path
 * the next position is checked
 */
checkPos(unsigned int moveDir)
{
    if ((ballPos1 + 1) ==  SIZEOFRAWMATR2)                              // out of bounds
    {
        missPlatform();
        return 0;
    }

    if (moveDir == UP)
    {
        if (ballPos1 < 1)                               // outer wall
        {
            changeDir();
            ballDirUp = FALSE;
            return 0;
        }
        else if(playField[ ballPos1 - 1][ ballPos2 ] == EMPTY)
            return 1;
        else if ( playField[ ballPos1 - 1 ][ ballPos2] == BLOCK )
        {
            removeBlock(ballPos1 - 1, ballPos2);
            ballDirUp = FALSE;
            changeDir();
            return 0;
        }

    }
    else if (moveDir == DOWN)
    {
        if(playField[ ballPos1 + 1][ ballPos2 ] == EMPTY)
            return 1;
        else if ( playField[ ballPos1 + 1 ][ ballPos2] == BLOCK )
        {
            removeBlock(ballPos1 + 1, ballPos2);
            ballDirUp = TRUE;
            changeDir();
            return 0;
        }
        else if (playField[ ballPos1 + 1][ ballPos2 ] == PLATFORM1 ||
                 playField[ ballPos1 + 1][ ballPos2 ] == PLATFORM2 ||
                 playField[ ballPos1 + 1][ ballPos2 ] == PLATFORM3 ||
                 playField[ ballPos1 + 1][ ballPos2 ] == PLATFORM4  )
        {
            platformHit = playField[ ballPos1 + 1][ ballPos2 ];
            changeDir_Platform();
            return 0;
        }

    }
    else if (moveDir == UPRIGHT)
    {
        if (ballPos1 < 1)                               // outer wall
        {
            changeDir();
            ballDirUp = FALSE;
            return 0;
        }
        if(playField[ ballPos1 - 1][ ballPos2 + 1 ] == EMPTY)
            return 1;
        else if ( playField[ ballPos1 - 1 ][ ballPos2 + 1] == BLOCK )
        {
            removeBlock(ballPos1 - 1, ballPos2 + 1);
            ballDirUp = FALSE;
            changeDir();
            return 0;
        }
        else if ((ballPos2 + 1) > (SIZEOFRAWMATR -1))                              // outer wall
        {
            changeDir();
            return 0;
        }

    }
    else if (moveDir == UPLEFT)
    {
        if (ballPos1 < 1)                               // outer wall
        {
            changeDir();
            ballDirUp = FALSE;
            return 0;
        }
        if(playField[ ballPos1 - 1][ ballPos2 - 1 ] == EMPTY)
            return 1;
        else if ( playField[ ballPos1 - 1 ][ ballPos2 - 1] == BLOCK )
        {
            removeBlock(ballPos1 - 1, ballPos2 - 1);
            ballDirUp = FALSE;
            changeDir();
            return 0;
        }
        else if ((ballPos2 - 1) < 0 )                 // outer wall
        {
            changeDir();
            return 0;
        }

    }
    else if (moveDir == DOWNRIGHT)
    {
        if(playField[ ballPos1 + 1][ ballPos2 +1 ] == EMPTY)
            return 1;
        else if ( playField[ ballPos1 + 1 ][ ballPos2 + 1] == BLOCK )
        {
            removeBlock(ballPos1 + 1, ballPos2 + 1 );
            ballDirUp = TRUE;
            changeDir();
            return 0;
        }
        else if (playField[ ballPos1 + 1][ ballPos2 + 1] == PLATFORM1 ||
                 playField[ ballPos1 + 1][ ballPos2 + 1] == PLATFORM2 ||
                 playField[ ballPos1 + 1][ ballPos2 + 1] == PLATFORM3 ||
                 playField[ ballPos1 + 1][ ballPos2 + 1] == PLATFORM4  )
        {
            platformHit = playField[ ballPos1 + 1][ ballPos2 + 1];
            changeDir_Platform();
            return 0;
        }
    }

    else if (moveDir == DOWNLEFT)
    {
        if(playField[ ballPos1 + 1][ ballPos2 - 1 ] == EMPTY)
            return 1;
        else if ( playField[ ballPos1 + 1 ][ ballPos2 - 1] == BLOCK )
        {
            removeBlock(ballPos1 + 1, ballPos2 - 1 );
            ballDirUp = TRUE;
            changeDir();
            return 0;
        }
        else if (playField[ ballPos1 + 1][ ballPos2 - 1] == PLATFORM1 ||
                 playField[ ballPos1 + 1][ ballPos2 - 1] == PLATFORM2 ||
                 playField[ ballPos1 + 1][ ballPos2 - 1] == PLATFORM3 ||
                 playField[ ballPos1 + 1][ ballPos2 - 1] == PLATFORM4  )
        {
            platformHit = playField[ ballPos1 + 1][ ballPos2 - 1];
            changeDir_Platform();
            return 0;
        }
    }


    else if (moveDir == RIGHT)
    {
        if(playField[ ballPos1][ ballPos2 +1 ] == EMPTY)
            return 1;
        else if (ballPos2 + 1 < 0)                               // outer wall
        {
            changeDir();
            return 0;
        }
    }

    else if (moveDir == LEFT)
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


/*
 * Ball movement path checks
 */
void
move_dir1()
{
    if(ballDirUp == TRUE )
    {
        if ((checkPos(UPLEFT)) == TRUE)
        {
            move_ball_upleft();
        }
    }
    else
    {
        if(checkPos(DOWNLEFT) == TRUE)
        {
            move_ball_downleft();
        }
    }
}
//
void
move_dir2()
{
    if(ballDirUp == TRUE)
    {
        if((upCounter == 0))
        {
            if(checkPos(UPLEFT) == TRUE)
            {
                move_ball_upleft();
            }
        }
        else
        {
            if(checkPos(UP) == TRUE)
            {
                move_ball_up();
            }
        }
    }
    else
    {
        if((upCounter == 0))
        {
            if(checkPos(DOWNLEFT) == TRUE)
            {
                move_ball_downleft();
            }
        }
        else
        {
            if(checkPos(DOWN) == TRUE)
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
move_dir3()
{
    if(ballDirUp == TRUE)
    {
        if(upCounter == 3)
        {
            if(checkPos(UPLEFT) == TRUE)
            {
                move_ball_upleft();
                upCounter = 0;
            }
        }
        else
        {
            if(checkPos(UP) == TRUE)
            {
                move_ball_up();
            }
        }
    }
    else
    {
        if(upCounter == 3)
        {
            if(checkPos(DOWNLEFT) == TRUE)
            {
                move_ball_downleft();
                upCounter = 0;
            }
        }
        else
        {
            if(checkPos(DOWN) == TRUE)
            {
                move_ball_down();
            }
        }
    }
    upCounter++;
}

void
move_dir4()
{
    if(ballDirUp == TRUE )
    {
        if(checkPos(UP) == TRUE)
        {
            move_ball_up();
        }
    }
    else
    {
        if(checkPos(DOWN) == TRUE)
        {
            move_ball_down();
        }
    }
}

void
move_dir5()
{
    if(ballDirUp == TRUE)
     {
         if(upCounter == 3)
         {
             if(checkPos(UPRIGHT) == TRUE)
             {
                 move_ball_upright();
                 upCounter = 0;
             }
         }
         else
         {
             if(checkPos(UP) == TRUE)
             {
                 move_ball_up();
             }
         }
     }
     else
     {
         if(upCounter == 3)
         {
             if(checkPos(DOWNRIGHT) == TRUE)
             {
                 move_ball_downright();
                 upCounter = 0;
             }
         }
         else
         {
             if(checkPos(DOWN) == TRUE)
             {
                 move_ball_down();
             }
         }
     }
     upCounter++;
}

void
move_dir6()
{
    if(ballDirUp == TRUE)
    {
        if(upCounter == 0)
        {
            if(checkPos(UPRIGHT) == TRUE)
            {
                move_ball_upright();
            }
        }
        else
        {
            if(checkPos(UP) == TRUE)
            {
                move_ball_up();
            }
        }
    }
    else
    {
        if(upCounter == 0)
        {
            if(checkPos(DOWNRIGHT) == TRUE)
            {
                move_ball_downright();
            }
        }
        else
        {
            if(checkPos(DOWN) == TRUE)
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
move_dir7()
{
    if(ballDirUp == TRUE )
    {
        if(checkPos(UPRIGHT) == TRUE)
        {
            move_ball_upright();
        }
    }
    else
    {
        if(checkPos(DOWNRIGHT) == TRUE)
        {
            move_ball_downright();
        }
    }
}


/*
 * Ball's actual movement control
 * ball is removed from the playfield,
 * it's new coordinates set then
 * it's readded to the field.
 */

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
move_ball_down()
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
    playField[ballPos1][ballPos2] = EMPTY;
}

void
move_ball_reAdd()
{
    playField[ballPos1][ballPos2] = BALL;
}
