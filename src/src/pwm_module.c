#include "pwm_module.h"

#include "stdint.h"
#include "xc.h"

#include "timer_defines.h"
#include "timer_functions.h"

#include "IO_Functions.h"

#define SET_PWM_TO_RB7() (_RP39R = 16) 


//Sets up Timer2 to be used for the OCx
void configure_timer(uint16_t us_period){
      T2CONbits.TON = 0;  //Makes sure that Timer is off. 
      setPrescaler(TIMER_2, PRE8);
      setPeriodTicks(TIMER_2, us_to_ticks(us_period, 8)-1);
}

//Sets up the OC Module to be used in PWM mode, and to use Timer2
void configure_output_compare(uint16_t us_period){

    OC1R = us_to_ticks(us_period >> 1, 8) - 1; //Defaults 50% Duty Cycle
    OC1CON1 = 0x0006; //
    OC1CON2 = 0x000C; //

}


//Initializes the PWM HW
void PWM_Init(uint16_t pin, uint16_t usPeriod){
    
    configure_timer(usPeriod);

    //Setup Pin
    setPinOut(1, pin);
    SET_PWM_TO_RB7();//TODO: make it mappable to any pin

    configure_output_compare(usPeriod);
}

//Starts the PWM signal
void startPWM(){
    T2CONbits.TON = 1;
}

void setHighTime(uint16_t usHigh){
    T2CONbits.TON = 0;
    OC1R = us_to_ticks(usHigh, 8) - 1;    
    T2CONbits.TON = 1;
}

uint16_t getHighTimeFloat(float input, float max_input, uint16_t us_max_period){
    return ((uint16_t)((input/max_input) * (float)us_max_period) + 0.5);
}