#ifndef _PWM_MODULE_H
#define _PWM_MODULE_H

#include "stdint.h"

#define NUM_OCxCON 1
#define OCxCON1_TIMER_SEL_PERIPHERAL 0x1C00
#define OCxCON1_TIMER_SEL_TIMER2 0x0000
#define OCxCON1_TIMER_SEL_TIMER3 0x0400
#define OCxCON1_MODE_SEL_EDGE_PWM 0x0006

//Enum for the various pins
typedef enum
{
    PWM_0 = 0
} PWM_Channel;

void PWM_Init(uint16_t pin, uint16_t usPeriod);

void PWM_setOCxCON1(PWM_Channel pwm_sel, uint16_t config_val);
void PWM_setOCxCLK(PWM_Channel pwm_sel, uint16_t clk_sel);
void PWM_setOCxMode(PWM_Channel pwm_sel, uint16_t clk_sel);

//Set Duty Cycle
void PWM_setHighTime(uint16_t usHigh);

uint16_t PWM_getPeriod();

#endif // _PWM_MODULE_H
