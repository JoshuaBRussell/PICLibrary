#ifndef _ENCODERS_H
#define _ENCODERS_H

#include "stdbool.h"
//TEST Specific Functions. TODO: Should possible move to a test specific header.

int getEncoderCount(void);

void isr_call(void);

int getTransistionTable(int index);



#endif // _ENCODERS_H
