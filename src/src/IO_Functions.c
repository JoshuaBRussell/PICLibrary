#include "IO_Functions.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>


uint16_t volatile * const TRIS_ARRY[NUM_PORTS] = { (uint16_t*)&TRISA,
                                                   (uint16_t*)&TRISB };

uint16_t volatile * const LAT_ARRY[NUM_PORTS] =  { (uint16_t*)&LATA,
                                                   (uint16_t*)&LATB };

uint16_t volatile * const PORT_ARRY[NUM_PORTS] =  { (uint16_t*)&PORTA,
                                                    (uint16_t*)&PORTB };

uint16_t volatile * const ODC_ARRY[NUM_PORTS] =  { (uint16_t*)&ODCA,
                                                   (uint16_t*)&ODCB };

uint16_t volatile * const PU_ARRY[NUM_PORTS]  =  { (uint16_t*)&CNPUA,
                                                   (uint16_t*)&CNPUB };

uint16_t volatile * const PD_ARRY[NUM_PORTS]  =  { (uint16_t*)&CNPDA,
                                                   (uint16_t*)&CNPDB };
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
            IO_setPinOut(port, pin);
        }
        else if (config[pin].Direction == INPUT){
            //IO_setPinIn(port, pin);
        }
        if(config[pin].State == HIGH){
            IO_setPinHigh(port, pin);
        }
        else if(config[pin].State == LOW){
            IO_setPinLow(port, pin);
        }
    }
}
void IO_setPinOut(PORT_Channel port, PIN_Channel pin){
    *(TRIS_ARRY[port]) &= (~(0x1 << pin));
}

void IO_setPinIn(PORT_Channel port, PIN_Channel pin){
    *(TRIS_ARRY[port]) |=  (0x1 << pin);
}

void IO_setPinHigh(PORT_Channel port, PIN_Channel pin){
    *(LAT_ARRY[port]) |=  (0x1 << pin);
}

void IO_setPinLow(PORT_Channel port, PIN_Channel pin){
    *(LAT_ARRY[port]) &= ~(0x1 << pin);
}

void IO_togglePin(PORT_Channel port, PIN_Channel pin){
    *(LAT_ARRY[port]) ^= (0x1 << pin);
}

void IO_setPinOD(PORT_Channel port, PIN_Channel pin){
    *(ODC_ARRY[port]) |=  (0x1 << pin);
}

void IO_setPinPU(PORT_Channel port, PIN_Channel pin){
    *(PU_ARRY[port]) |=  (0x1 << pin);
}

void IO_setPinPD(PORT_Channel port, PIN_Channel pin){
    *(PD_ARRY[port]) |=  (0x1 << pin);
}

bool IO_readPin(PORT_Channel port, PIN_Channel pin){
    return (*(PORT_ARRY[port]) & (0x1 << pin));
}
