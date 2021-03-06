/*
 * logic.h
 *
 *  Created on: 18 Apr 2017
 *      Author: Y009
 */

#ifndef LOGIC_H_
#define LOGIC_H_


void logic_init();
void logic_cyclic();

/*
 *  Numbers to display score with.
 */

#define BLANK { \
    {0,0,0,0,0,0,0}, \
    {0,0,0,0,0,0,0},\
    {0,0,0,0,0,0,0},\
    {0,0,0,0,0,0,0},\
    {0,0,0,0,0,0,0},\
    {0,0,0,0,0,0,0},\
    {0,0,0,0,0,0,0},\
    {0,0,0,0,0,0,0},\
    {0,0,0,0,0,0,0},\
    {0,0,0,0,0,0,0}\
}

#define LED0 {\
    {0,0,0,0,0,0,0},\
    {0,0,1,1,1,0,0},\
    {0,1,0,0,0,1,0},\
    {0,1,0,0,1,1,0},\
    {0,1,0,1,0,1,0},\
    {0,1,1,0,0,1,0},\
    {0,1,0,0,0,1,0},\
    {0,1,0,0,0,1,0},\
    {0,0,1,1,1,0,0},\
    {0,0,0,0,0,0,0}\
}

#define LED1 {\
    {0,0,0,0,0,0,0},\
    {0,0,0,1,1,0,0},\
    {0,0,1,0,1,0,0},\
    {0,1,0,0,1,0,0},\
    {0,0,0,0,1,0,0},\
    {0,0,0,0,1,0,0},\
    {0,0,0,0,1,0,0},\
    {0,0,0,0,1,0,0},\
    {0,0,0,0,1,0,0},\
    {0,0,0,0,0,0,0}\
}

#define LED2 {\
    {0,0,0,0,0,0,0},\
    {0,0,1,1,1,0,0},\
    {0,1,0,0,0,1,0},\
    {0,0,0,0,0,1,0},\
    {0,0,0,0,0,1,0},\
    {0,0,0,0,1,0,0},\
    {0,0,0,1,0,0,0},\
    {0,0,1,0,0,0,0},\
    {0,1,1,1,1,1,0},\
    {0,0,0,0,0,0,0}\
}

#define LED3 {\
    {0,0,0,0,0,0,0},\
    {0,1,1,1,1,1,0},\
    {0,0,0,0,0,1,0},\
    {0,0,0,0,1,0,0},\
    {0,0,0,1,0,0,0},\
    {0,0,0,0,1,0,0},\
    {0,0,0,0,0,1,0},\
    {0,1,0,0,0,1,0},\
    {0,0,1,1,1,0,0},\
    {0,0,0,0,0,0,0}\
}

#define LED4 {\
    {0,0,0,0,0,0,0},\
    {0,0,0,0,1,0,0},\
    {0,0,0,1,1,0,0},\
    {0,0,1,0,1,0,0},\
    {0,1,0,0,1,0,0},\
    {0,1,1,1,1,1,0},\
    {0,0,0,0,1,0,0},\
    {0,0,0,0,1,0,0},\
    {0,0,0,0,1,0,0},\
    {0,0,0,0,0,0,0}\
}

#define LED5 {\
    {0,0,0,0,0,0,0},\
    {0,1,1,1,1,1,0},\
    {0,1,0,0,0,0,0},\
    {0,1,0,0,0,0,0},\
    {0,1,1,1,1,1,0},\
    {0,0,0,0,0,1,0},\
    {0,0,0,0,0,1,0},\
    {0,1,0,0,0,1,0},\
    {0,0,1,1,1,0,0},\
    {0,0,0,0,0,0,0}\
}

#define LED6 {\
    {0,0,0,0,0,0,0},\
    {0,0,0,0,1,1,0},\
    {0,0,0,1,0,0,0},\
    {0,0,1,0,0,0,0},\
    {0,1,0,0,0,0,0},\
    {0,1,1,1,1,0,0},\
    {0,1,0,0,0,1,0},\
    {0,1,0,0,0,1,0},\
    {0,0,1,1,1,0,0},\
    {0,0,0,0,0,0,0}\
}

#define LED7 {\
    {0,0,0,0,0,0,0},\
    {0,1,1,1,1,1,0},\
    {0,1,0,0,0,1,0},\
    {0,0,0,0,1,0,0},\
    {0,0,0,1,0,0,0},\
    {0,0,1,0,0,0,0},\
    {0,0,1,0,0,0,0},\
    {0,0,1,0,0,0,0},\
    {0,0,1,0,0,0,0},\
    {0,0,0,0,0,0,0}\
}

#define LED8 {\
    {0,0,0,0,0,0,0},\
    {0,0,1,1,1,0,0},\
    {0,1,0,0,0,1,0},\
    {0,1,0,0,0,1,0},\
    {0,0,1,1,1,0,0},\
    {0,1,0,0,0,1,0},\
    {0,1,0,0,0,1,0},\
    {0,1,0,0,0,1,0},\
    {0,0,1,1,1,0,0},\
    {0,0,0,0,0,0,0}\
}

#define LED9 {\
    {0,0,0,0,0,0,0},\
    {0,0,1,1,1,0,0},\
    {0,1,0,0,0,1,0},\
    {0,1,0,0,0,1,0},\
    {0,0,1,1,1,1,0},\
    {0,0,0,0,0,1,0},\
    {0,0,0,0,0,1,0},\
    {0,0,0,0,1,0,0},\
    {0,0,1,1,0,0,0},\
    {0,0,0,0,0,0,0}\
}


#endif /* LOGIC_H_ */
