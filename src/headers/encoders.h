#ifndef _ENCODERS_H
#define _ENCODERS_H

#include "stdint.h"
#include "stdbool.h"
#include "IO_Functions.h"

/*----------------------------------------------------------------------------//
//Defines                                                                     //
/*----------------------------------------------------------------------------*/

#define TICKS_PER_REV 64.0
#define TICKS_TO_RADS_SF (6.283185/TICKS_PER_REV)

typedef struct{

    //Paramaters
    PORT_Channel port;
    PIN_Channel pinA;
    PIN_Channel pinB;

    volatile long prev_enc_count;
    volatile long enc_count;
    unsigned int enc_state;

} ENC;

/*----------------------------------------------------------------------------//
// Functions for using a Quad Encoder with interrupts. Currently uses x4
// Encoding.   
//----------------------------------------------------------------------------*/

//Initialize Encoders. Currently Pins must be on the same port and must be consecutive 
//to one another (e.g. pins 5/6). 
void ENC_setupEncoders(ENC* enc_obj, PORT_Channel port, PIN_Channel pinA, PIN_Channel pinB);

float ENC_getEncoder_Rads_per_sec(float delta_t_sec);

//Getters
PORT_Channel ENC_getENCPort(ENC* enc);
PIN_Channel ENC_getENCPinA(ENC* enc);
PIN_Channel ENC_getENCPinB(ENC* enc);
long ENC_getENCCount(ENC* enc);
long ENC_getPrevENCCount(ENC* enc);
unsigned int ENC_getENCState(ENC* enc);

bool isISRCalled();

#endif // _ENCODERS_H
