#include "timer_functions.h"

#include <xc.h>
#include <stdbool.h>

#define INSTR_CLOCK 3.69E6
#define NUM_TIMERS 2

#define TIMER_ON_BIT_MASK  0x8000
#define TIMER_OFF_BIT_MASK 0x0000

#define TIMER_PRE_LOC 0x0030
#define TIMER_PRE_OFFSET 4

#define INTERRUPT_PRIOTIY_MAX (7)

uint16_t volatile * const TIMR_ARRY[NUM_TIMERS] = { (uint16_t*)&T2CON, (uint16_t*)&T3CON};

uint16_t volatile * const PERIOD_ARRY[NUM_TIMERS] = { (uint16_t*)&PR2, (uint16_t*)&PR3};


uint16_t ms_to_ticks(uint16_t ms, uint16_t pre){
    float f_ticks = (ms*INSTR_CLOCK)/(1000*pre); 
    return (uint16_t)(f_ticks + 0.5);
}

uint16_t us_to_ticks(uint16_t us, uint16_t pre){
    float f_ticks = (us*INSTR_CLOCK)/(1000000*pre); 
    return (uint16_t)(f_ticks + 0.5);
}


void turnTimerOn(Timer_Channel timer){
    *(TIMR_ARRY[timer]) |= TIMER_ON_BIT_MASK; 
}

void setPeriodTicks(Timer_Channel timer, uint16_t ticks){
    *(PERIOD_ARRY[timer]) = ticks;
}

void setPrescaler(Timer_Channel timer, PRE_SEL PRE){
    *(TIMR_ARRY[timer]) = (~(TIMER_PRE_LOC) & *(TIMR_ARRY[timer])) | (PRE << TIMER_PRE_OFFSET); //Clears then Sets
}

bool isTimer2Expired(){
    return _T2IF;
}

bool isTimer3Expired(){
    return _T3IF;
}

void clearTimer2IntFlag(void){
    _T2IF = 0;
}

void clearTimer3IntFlag(void){
    _T3IF = 0;
}

void setTimer2IntEn(bool flag){
    _T2IE = flag;
}

void setTimer3IntEn(bool flag){
    _T3IE = flag;
}

void setTimer2IntPriority(uint8_t priority){
    
    if(priority > INTERRUPT_PRIOTIY_MAX) {return;}
    _T2IP = priority;
}

void setTimer3IntPriority(uint8_t priority){
    
    if(priority > INTERRUPT_PRIOTIY_MAX) {return;}
    _T2IP = priority;
}