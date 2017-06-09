#include "IO_Functions.h"
#include "IO_Defines.h"

uint16_t volatile * const TRIS_ARRY[NUM_PORTS] = { (uint16_t*)&TRISA,
                                                   (uint16_t*)&TRISB };

uint16_t volatile * const LAT_ARRY[NUM_PORTS] =  { (uint16_t*)&LATA,
                                                   (uint16_t*)&LATB };

void setB15Out(){
    *(TRIS_ARRY[1]) = 0x7FFF;
}

void B15On(){
    *(LAT_ARRY[1]) = 0xFFFF;
}
void B15Off(){
    *(LAT_ARRY[1]) = 0x7FFF;
}
