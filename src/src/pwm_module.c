#include "pwm_module.h"
#include <stdint.h>
#include "stdint.h"
#include "xc.h"
#include "timer_functions.h"

#include "IO_Functions.h"

#define OCxCON1_TIMER_SEL_LOC 0x1C00
#define OCxCON1_MODE_SEL_LOC 0x0007 

#define SET_PWM_TO_RB7() (_RP39R = 16)


uint16_t volatile * const OCxCON1_ARRY[NUM_PORTS] = { (uint16_t*)&OC1CON1};


//Sets up PWM as singleton TODO: Change to non singleton
static uint16_t PWM_PERIOD = 2000;

void PWM_setOCxCON1(PWM_Channel pwm_sel, uint16_t config_val){
    *(OCxCON1_ARRY[pwm_sel]) = config_val;
}

void PWM_setOCxCLK(PWM_Channel pwm_sel, uint16_t clk_sel){
    *(OCxCON1_ARRY[pwm_sel]) = (~(OCxCON1_TIMER_SEL_LOC) & *(OCxCON1_ARRY[0])) | clk_sel; //Clears first, then sets
}

void PWM_setOCxMode(PWM_Channel pwm_sel, uint16_t mode_sel){
    *(OCxCON1_ARRY[pwm_sel]) = (~(OCxCON1_MODE_SEL_LOC) & *(OCxCON1_ARRY[0])) | mode_sel; //Clears first, then sets
}

//Sets up the OC Module to be used in PWM mode, and; to use Timer2
void configure_output_compare(uint16_t us_period){

    OC1R = 0x0000;//Defaults to 0% duty cycle
    OC1RS = us_to_ticks(us_period, 1);//pre = 1 -> no prescale
    PWM_setOCxMode(PWM_0, OCxCON1_MODE_SEL_EDGE_PWM); 
    PWM_setOCxCLK(PWM_0, OCxCON1_TIMER_SEL_PERIPHERAL);
    OC1CON2 = 0x009F; //Triggers OCx based off SyncSel & OCxRS compare event is used for synchronization

}

//Initializes the PWM HW
void PWM_Init(uint16_t pin, uint16_t usPeriod){
    
    //Setup Pin
    setPinOut(1, pin);
    SET_PWM_TO_RB7();//TODO: make it mappable to any pin

    configure_output_compare(usPeriod);
}

void PWM_setHighTime(uint16_t usHigh){

    OC1R = us_to_ticks(usHigh, 1); //pre = 1 -> no prescale  
}

uint16_t PWM_getPeriod(){
    return PWM_PERIOD;
}

