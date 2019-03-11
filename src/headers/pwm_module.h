#ifndef _PWM_MODULE_H
#define _PWM_MODULE_H

#include "stdint.h"

#define NUM_OCxCON 1 //Total number of Output Comapares

typedef enum
{
    OC_MODE_EDGE_PWM = 6,
    OC_MODE_CENTER_PWM = 7
} OC_MODE_SEL;

typedef enum
{
    OC_CLOCK_TIMER_2 = 0,
    OC_CLOCK_TIMER_3 = 1,
    OC_CLOCK_PERIPHERAL = 7
} OC_CLOCK_SEL;

typedef enum
{
    PWM_0 = 0
} PWM_Channel;

typedef enum
{
    OC_TRIG_SYNC = 0,
    OC_TRIG_TRIG
}  OC_TRIG_SEL;

typedef enum
{
    OC_SYNC_SEL_OCxRS = 0x1F,
} OC_SYNC_SOURCE_SEL;


//TODO: Make all references to using Output Compare hidden. That way it looks like a pure PWM interface to the user. And so,
//implementation details are hidden. 
void PWM_Init(uint16_t pin, uint16_t us_period);              //The names of these functions need to change but that is all. Since they are what one would expect in a PWM interface.
void PWM_setOCCLK(PWM_Channel pwm_sel, OC_CLOCK_SEL clk_sel); //"PWM Source Clock"
void PWM_setOCMode(PWM_Channel pwm_sel, OC_MODE_SEL mode_sel); //"PWM -> Center/Edge Aligned"
void PWM_setOCR(PWM_Channel pwm_sel, uint16_t ocr_val); //"PWM setHighTime"
void PWM_setOCRS(PWM_Channel pwm_sel, uint16_t ocrs_val); //"PWM setPeriod"
//Set Duty Cycle
void PWM_setHighTime(uint16_t usHigh);
void PWM_setScaledOutput(PWM_Channel pwm_sel, float scale_factor);
uint16_t PWM_getOCRS(PWM_Channel pwm_sel);

//These functions are implementation specific, and need to be hidden in the implementation file. Or EVEN BETTER and Output Compare Interface Module needs 
//to be made, and the PWM calls its interface to create a PWM module. 
void PWM_setOCCON1(PWM_Channel pwm_sel, uint16_t reg_val);
void PWM_setOCTrig(PWM_Channel pwm_sel, OC_TRIG_SEL trig_sel);
void PWM_setOCSyncSel(PWM_Channel pwm_sel, OC_SYNC_SOURCE_SEL sync_source);

#endif // _PWM_MODULE_H
