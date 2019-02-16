#include "pwm_module.h"
#include <stdint.h>
#include "stdint.h"
#include "xc.h"
#include "timer_functions.h"

#include "IO_Functions.h"

#define OCxCON1_TIMER_SEL_LOC 0x1C00
#define OC_CLOCK_SEL_BIT_OFFSET 10

#define OCxCON1_MODE_SEL_LOC 0x0007
#define OC_MODE_SEL_BIT_OFFSET 0 

#define OCxCON2_TRIG_SEL_LOC 0x0080
#define OC_TRIG_SEL_BIT_OFFSET 7

#define OCxCON2_SYNC_SRC_LOC 0x001F
#define OC_SYNC_SRC_BIT_OFFSET 0

#define SET_PWM_TO_RB7() (_RP39R = 16)


uint16_t volatile * const OCxCON1_ARRY[NUM_PORTS] = { (uint16_t*)&OC1CON1};

uint16_t volatile * const OCxCON2_ARRY[NUM_PORTS] = { (uint16_t*)&OC1CON2};

uint16_t volatile * const OCxR_ARRY[NUM_PORTS] = { (uint16_t*)&OC1R};

uint16_t volatile * const OCxRS_ARRY[NUM_PORTS] = { (uint16_t*)&OC1RS};


void PWM_setOCCON1(PWM_Channel pwm_sel, uint16_t reg_val){
    *(OCxCON1_ARRY[pwm_sel]) = reg_val;
}

void PWM_setOCCLK(PWM_Channel pwm_sel, OC_CLOCK_SEL clk_sel){
    *(OCxCON1_ARRY[pwm_sel]) = (~(OCxCON1_TIMER_SEL_LOC) & *(OCxCON1_ARRY[pwm_sel])) | (clk_sel << OC_CLOCK_SEL_BIT_OFFSET); //Clears first, then sets
}

void PWM_setOCMode(PWM_Channel pwm_sel, OC_MODE_SEL mode_sel){
    *(OCxCON1_ARRY[pwm_sel]) = (~(OCxCON1_MODE_SEL_LOC) & *(OCxCON1_ARRY[pwm_sel])) | (mode_sel << OC_MODE_SEL_BIT_OFFSET); //Clears first, then sets
}

void PWM_setOCR(PWM_Channel pwm_sel, uint16_t ocr_val){
    *(OCxR_ARRY[pwm_sel]) = ocr_val;
}

void PWM_setOCRS(PWM_Channel pwm_sel, uint16_t ocrs_val){
    *(OCxRS_ARRY[pwm_sel]) = ocrs_val;
}

void PWM_setOCTrig(PWM_Channel pwm_sel, OC_TRIG_SEL trig_sel){
    *(OCxCON2_ARRY[pwm_sel]) = (~(OCxCON2_TRIG_SEL_LOC) & *(OCxCON2_ARRY[pwm_sel])) | (trig_sel << OC_TRIG_SEL_BIT_OFFSET); //Clears first, then sets
}

void PWM_setOCSyncSel(PWM_Channel pwm_sel, OC_SYNC_SOURCE_SEL sync_source){
    *(OCxCON2_ARRY[pwm_sel]) = (~(OCxCON2_SYNC_SRC_LOC) & *(OCxCON2_ARRY[pwm_sel])) | (sync_source << OC_SYNC_SRC_BIT_OFFSET); //Clears first, then sets
}

//Initializes the PWM HW
void PWM_Init(uint16_t pin, uint16_t us_period){
    
    //Setup Pin
    setPinOut(1, pin);
    SET_PWM_TO_RB7();//TODO: make it mappable to any pin

    PWM_setOCR(PWM_0, 0x0000);//Defaults to 0% duty cycle
    PWM_setOCRS(PWM_0, us_to_ticks(us_period, 1));//pre = 1 -> no prescale
    PWM_setOCMode(PWM_0, OC_MODE_EDGE_PWM); 
    PWM_setOCCLK(PWM_0, OC_CLOCK_PERIPHERAL);
    PWM_setOCTrig(PWM_0, OC_TRIG_TRIG);
    PWM_setOCSyncSel(PWM_0, OC_SYNC_SEL_OCxRS);
}

void PWM_setHighTime(uint16_t usHigh){

    PWM_setOCR(PWM_0, us_to_ticks(usHigh, 1)); //pre = 1 -> no prescale  
}

uint16_t PWM_getPeriod(PWM_Channel pwm_sel){
    return *(OCxRS_ARRY[pwm_sel]);
}

