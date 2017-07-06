#ifndef _TIMER_FUNCTIONS_H
#define _TIMER_FUNCTIONS_H


#include "Timer_Defines.h"
#include <stdint.h>
#include <stdbool.h>



//----Timer Utility Functions----//
uint16_t ms_to_ticks(uint16_t ms, uint16_t pre);

//----Timer Configuration Functions----//
void turnTimerOn(Timer_Channel timer);

void setPeriodTicks(Timer_Channel timer, uint16_t ticks);

void setPrescaler(Timer_Channel timer, PRE_SEL PRE);

bool isTimer2Expired(void);

bool clearTimer2IntFlag(void);

void setTimer2IntEn(bool bit);

void setTimer2IntPriority(uint8_t priority);

#endif // _TIMER_FUNCTIONS_H
