#include "pwm_module.h"

#include "stdint.h"
#include "xc.h"
#include "timer_functions.h"

#include "IO_Functions.h"

#define SET_PWM_TO_RB7() (_RP39R = 16) 

//Sets up PWM as singleton TODO: Change to non singleton
static uint16_t PWM_PERIOD = 2000;

// //Sets up Timer2 to be used for the OCx
// void configure_timer(uint16_t us_period){
//       T2CONbits.TON = 0;  //Makes sure that Timer is off. 
//       setPrescaler(TIMER_2, PRE8);
//       setPeriodTicks(TIMER_2, us_to_ticks(us_period, 8)-1);
// }

//Sets up the OC Module to be used in PWM mode, and to use Timer2
void configure_output_compare(uint16_t us_period){

    OC1R = 0x0000;//Defaults to 0% duty cycle
    OC1RS = 0x4000;
    OC1CON1 = 0x1C06; //Peripheral Clock and Edge Alighned PWM
    OC1CON2 = 0x009F; //Triggers OCx based off SyncSel & OCxRS compare event is used for synchronization

}


//Initializes the PWM HW
void PWM_Init(uint16_t pin, uint16_t usPeriod){
    
    //configure_timer(usPeriod);

    //Setup Pin
    setPinOut(1, pin);
    SET_PWM_TO_RB7();//TODO: make it mappable to any pin

    configure_output_compare(usPeriod);
}

//Starts the PWM signal
// void startPWM(){
//     T2CONbits.TON = 1;
// }

void PWM_setHighTime(uint16_t usHigh){
    // T2CONbits.TON = 0;
    OC1R = 0x2000;//us_to_ticks(usHigh, 8) - 1;    
    // T2CONbits.TON = 1;
}

uint16_t PWM_getPeriod(){
    return PWM_PERIOD;
}

