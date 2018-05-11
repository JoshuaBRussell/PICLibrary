#ifndef _PWM_MODULE_H
#define _PWM_MODULE_H

#include "stdint.h"

void PWM_Init(uint16_t pin, uint16_t usPeriod);

void startPWM();

//Set Duty Cycle
void setHighTime(uint16_t usHigh);

//Helper function that converts a float input with an expected float max value to a proportional high time 
//for the PWM. 
uint16_t getHighTimeFloat(float input, float max_input, uint16_t us_max_period);
#endif // _PWM_MODULE_H
