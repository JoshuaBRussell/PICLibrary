#ifndef _ENCODERS_H
#define _ENCODERS_H

#include "stdint.h"
#include "stdbool.h"
#include "IO_Functions.h"

/*----------------------------------------------------------------------------//
//Defines                                                                     //
/*----------------------------------------------------------------------------*/

typedef struct ENC_obj* ENC_Handle;

/*----------------------------------------------------------------------------//
// Functions for using a Quad Encoder with interrupts. Currently uses x4
// Encoding.   
//----------------------------------------------------------------------------*/

//Initialize Encoders. Currently Pins must be on the same port and must be consecutive 
//to one another (e.g. pins 5/6). 
ENC_Handle ENC_setupEncoders(PORT_Channel port, PIN_Channel pinA, PIN_Channel pinB,
                       float TICKS_PER_REV);


//Getters
PORT_Channel ENC_getENCPort(ENC_Handle enc);
PIN_Channel ENC_getENCPinA(ENC_Handle enc);
PIN_Channel ENC_getENCPinB(ENC_Handle enc);
long ENC_getENCCount(ENC_Handle enc);
long ENC_getPrevENCCount(ENC_Handle enc);
unsigned int ENC_getENCState(ENC_Handle enc);
float ENC_getENCVel(ENC_Handle enc, float delta_t_sec);


#endif // _ENCODERS_H
