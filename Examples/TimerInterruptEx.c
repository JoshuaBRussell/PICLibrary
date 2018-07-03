
////////////////////////////////////////////////////////////////////
//
//  Example Timer Interrupt Function that toggles B15 every second.
//
////////////////////////////////////////////////////////////////////
#include "xc.h"
#include "main.h"
#include "IO_Functions.h"
#include "IO_Defines.h"
#include "timer_functions.h"
#include "timer_defines.h"

void _ISR _T2Interrupt(void){
    togglePin(1, 15);
    clearTimer2IntFlag();
    
}

void simple_delay(){
    int i = 0;
    int j = 0;
    for(i = 0; i < 100; i++){
        for(j = 0; j < 200; j++){

        }
    }
}
int main(){
    setPinOut(1, 15);
    setPrescaler(TIMER_2, PRE64);
    setPeriodTicks(TIMER_2, ms_to_ticks(1000, 64));
    
    clearTimer2IntFlag();
    setTimer2IntPriority(1);
    setTimer2IntEn(true);
    turnTimerOn(TIMER_2);

    while(1){

    }




}