#include "xc.h"
#include "main.h"
#include "IO_Functions.h"
#include "timer_functions.h"
#include "pwm_module.h"
#include "stdint.h"

#define usPeriod 3450
#define timeHigh 1500


int main(){


    //Makes sure that Timer is Off
    T2CONbits.TON = 0;

    PWM_Init(7, usPeriod);

    //Output starts on first call
    PWM_setHighTime(timeHigh);
    
    //startPWM();
    
    while(1){
    
    }    




}