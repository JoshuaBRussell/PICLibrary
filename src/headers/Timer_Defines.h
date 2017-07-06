#ifndef _TIMER_DEFINES_H
#define _TIMER_DEFINES_H

typedef enum
{
    TIMER_2 = 0
} Timer_Channel;

typedef enum
{
    PRE1 = 0,
    PRE8 = 1,
    PRE64 = 2,
    PRE256 = 3
} PRE_SEL;

#define TIMER_ON_BIT_MASK  0x8000
#define TIMER_OFF_BIT_MASK 0x0000

#define TIMER_PRE_LOC 0x0030
#define TIMER_PRE_256_BIT_MASK 0x0030
#define TIMER_PRE_64_BIT_MASK  0x0020
#define TIMER_PRE_8_BIT_MASK   0x0010
#define TIMER_PRE_1_BIT_MASK   0x0000

#endif