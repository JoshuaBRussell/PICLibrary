#ifndef _TIMER_DEFINES_H
#define _TIMER_DEFINES_H

//Used to specify which HW Timer counter to use
typedef enum
{
    TIMER_2 = 0,
    TIMER_3
} Timer_Channel;

//Used to specify which Prescaler value to use.
typedef enum
{
    PRE1 = 0,
    PRE8 = 1,
    PRE64 = 2,
    PRE256 = 3
} PRE_SEL;

#endif