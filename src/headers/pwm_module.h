#ifndef _PWM_MODULE_H
#define _PWM_MODULE_H

#include "stdint.h"

void PWM_Init(uint16_t pin, uint16_t usPeriod);

void startPWM();

//Set Duty Cycle
void setHighTime(uint16_t usHigh);
#endif // _PWM_MODULE_H
