#include "timer_functions.h"

#include <xc.h>
#include "Timer_Defines.h"
#include <stdbool.h>

#define INSTR_CLOCK 3.69E6
#define NUM_TIMERS 1

uint16_t volatile * const TIMR_ARRY[NUM_TIMERS] = { (uint16_t*)&T2CON};

uint16_t volatile * const PERIOD_ARRY[NUM_TIMERS] = { (uint16_t*)&PR2};


uint16_t ms_to_ticks(uint16_t ms, uint16_t pre){
    float f_ticks = (ms*INSTR_CLOCK)/(1000*pre); 
    return (uint16_t)(f_ticks + 0.5);
}


void turnTimerOn(Timer_Channel timer){
    *(TIMR_ARRY[timer]) |= TIMER_ON_BIT_MASK; 
}

void setPeriodTicks(Timer_Channel timer, uint16_t ticks){
    *(PERIOD_ARRY[timer]) = ticks;
}

void setPrescaler(Timer_Channel timer, PRE_SEL PRE){

    switch(PRE){
        case(PRE1):
            *(TIMR_ARRY[timer]) = (~(TIMER_PRE_LOC) & *(TIMR_ARRY[timer])) | TIMER_PRE_1_BIT_MASK;
            break;

        case(PRE8):
            *(TIMR_ARRY[timer]) = (~(TIMER_PRE_LOC) & *(TIMR_ARRY[timer])) | TIMER_PRE_8_BIT_MASK;
            break;

        case(PRE64):
            *(TIMR_ARRY[timer]) = (~(TIMER_PRE_LOC) & *(TIMR_ARRY[timer])) | TIMER_PRE_64_BIT_MASK;
            break;

        case(PRE256):
            *(TIMR_ARRY[timer]) = (~(TIMER_PRE_LOC) & *(TIMR_ARRY[timer])) | TIMER_PRE_256_BIT_MASK;
            break;
        
    }
}

bool isTimer2Expired(){
    return _T2IF;
}

bool clearTimer2IntFlag(void){
    _T2IF = 0;
}

void setTimer2IntEn(bool flag){
    _T2IE = flag;
}

void setTimer2IntPriority(uint8_t priority){
    //TODO: Add Interrupt Priority Level Max(this removing this magic number)
    if(priority > 7) {return;}
    _T2IP = priority;
}