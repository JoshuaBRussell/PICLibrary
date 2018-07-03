
////////////////////////////////////////////////////////////////////
//
//  Example using the Encoders. Outputs count value onto PWM output
//
////////////////////////////////////////////////////////////////////
#include "xc.h"
#include "main.h"
#include "IO_Functions.h"
#include "timer_functions.h"
#include "encoders.h"
#include "pwm_module.h"

void _ISR _T3Interrupt(void){
    togglePin(1, 15);
    clearTimer3IntFlag();

    if(getEncoderCount() >= 0){
        setHighTime(getEncoderCount());
    }
    else {
        setHighTime(-1*getEncoderCount());
    }
    
}

int main(){
    setPinOut(1, 15);

    setupEncoders(1, 5, 6);


    setPrescaler(TIMER_3, PRE64);
    setPeriodTicks(TIMER_3, ms_to_ticks(10, 64));
    clearTimer3IntFlag();
    setTimer3IntPriority(1);
    setTimer3IntEn(true);

    turnTimerOn(TIMER_3);

    T2CONbits.TON = 0;

    PWM_Init(7, 2000);
    setHighTime(0);
    
    startPWM();

    while(1){

    }




}