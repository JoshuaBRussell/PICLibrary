#include "xc.h"
#include "main.h"
#include "IO_Functions.h"
#include "timer_functions.h"
#include "pwm_module.h"
#include "stdint.h"

#define usPeriod 4450
#define timeHigh1 1340
#define timeHigh2 2000


int main(){

    setPinOut(2, 5);
    PWM_Init(7, usPeriod);

    //Output starts on first call
    togglePin(2, 5);
    PWM_setHighTime(timeHigh1);

    int i = 0;
    while (i < 50){i++;}
    togglePin(2,5);
    PWM_setHighTime(timeHigh2);
    //startPWM();
    
    while(1){
    
    }    




}