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

void PWM_Init(uint16_t pin, uint16_t us_period);

void PWM_setOCCON1(PWM_Channel pwm_sel, uint16_t reg_val);
void PWM_setOCCLK(PWM_Channel pwm_sel, OC_CLOCK_SEL clk_sel);
void PWM_setOCMode(PWM_Channel pwm_sel, OC_MODE_SEL mode_sel);
void PWM_setOCR(PWM_Channel pwm_sel, uint16_t ocr_val);
void PWM_setOCRS(PWM_Channel pwm_sel, uint16_t ocrs_val);
void PWM_setOCTrig(PWM_Channel pwm_sel, OC_TRIG_SEL trig_sel);
void PWM_setOCSyncSel(PWM_Channel pwm_sel, OC_SYNC_SOURCE_SEL sync_source);

//Set Duty Cycle
void PWM_setHighTime(uint16_t usHigh);

uint16_t PWM_getPeriod();

#endif // _PWM_MODULE_H
