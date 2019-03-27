#include "xc.h"


void setup_FRC_w_PLL(){
    //Fosc = Fin(FRC)*(M/(N2*N2))
    PLLFBD = 63; //M = 65
    CLKDIVbits.PLLPOST = 0; // N2 = 2
    CLKDIVbits.PLLPRE = 1; // N1 = 3

    //Init clock switch to prim with osc
    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(OSCCON | 0x01);

    //wait for clock switch to occur
    while(OSCCONbits.COSC != 0b001);

    // Wait for PLL to lock
    while (OSCCONbits.LOCK != 1);
}