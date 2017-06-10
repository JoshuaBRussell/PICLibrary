#include "IO_Functions.h"

#include <xc.h>
#include <stdint.h>

uint16_t volatile * const TRIS_ARRY[NUM_PORTS] = { (uint16_t*)&TRISA,
                                                   (uint16_t*)&TRISB };

uint16_t volatile * const LAT_ARRY[NUM_PORTS] =  { (uint16_t*)&LATA,
                                                   (uint16_t*)&LATB };


void setPinOut(uint16_t port, uint16_t pin ){
    *(TRIS_ARRY[port]) &= (~(0x1 << pin));
}

void setPinHigh(uint16_t port, uint16_t pin){
    *(LAT_ARRY[port]) |=  (0x1 << pin);
}

void togglePin(uint16_t port, uint16_t pin){
    *(LAT_ARRY[port]) ^= (0x1 << pin);
}
