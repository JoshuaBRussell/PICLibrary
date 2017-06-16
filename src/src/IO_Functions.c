#include "IO_Functions.h"

#include <xc.h>
#include <stdint.h>


uint16_t volatile * const TRIS_ARRY[NUM_PORTS] = { (uint16_t*)&TRISA,
                                                   (uint16_t*)&TRISB };

uint16_t volatile * const LAT_ARRY[NUM_PORTS] =  { (uint16_t*)&LATA,
                                                   (uint16_t*)&LATB };

void IO_Config(const PIN_CONFIG * config){
    uint16_t index = 0;
    uint16_t pin = 0;
    uint16_t port = 0;

    // Although this will work, the loop makes it slow,
    // and the function calls should probably be inlined at the least.
    for(index = 0; index < TOTAL_IO_PINS; index++){
        pin = index % IO_PINS_PER_PORT;
        port = index / IO_PINS_PER_PORT;

        if(config[pin].Direction == OUTPUT){
            setPinOut(port, pin);
        }
        //TODO: Implement setPinIn() function
        else if (config[pin].Direction == INPUT){
            //setPinIn(port, pin);
        }
        if(config[pin].State == HIGH){
            setPinHigh(port, pin);
        }
        else if(config[pin].State == LOW){
            setPinLow(port, pin);
        }
    }
}
void setPinOut(uint16_t port, uint16_t pin ){
    *(TRIS_ARRY[port]) &= (~(0x1 << pin));
}

void setPinHigh(uint16_t port, uint16_t pin){
    *(LAT_ARRY[port]) |=  (0x1 << pin);
}

void setPinLow(uint16_t port, uint16_t pin){
    *(LAT_ARRY[port]) &= ~(0x1 << pin);
}

void togglePin(uint16_t port, uint16_t pin){
    *(LAT_ARRY[port]) ^= (0x1 << pin);
}
