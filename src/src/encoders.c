#include "encoders.h"
#include "stdbool.h"
#include "stdint.h"
#include "IO_Functions.h"
#include "xc.h"

//TODO: Remove dependencies on LOW level HW?

//#define PINS_SEL_BIT_MASK 0x00060

//TODO: Move these into an Encoder_Data struct. This will make it more modular, and allow for multiple encoders.
volatile static long prev_enc_count = 0; 
volatile static long enc_count = 0;
static uint16_t PINS_SEL_BIT_MASK = 0x0000;

//Selects whether to increment/decrement the encoder count depending on the state change of the encoder. 
static int transistion_table[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

/* Represents the readings of the A/B lines as states.
// The previous state and current state are concatenated,  
// and the resulting value is used as an index for the transition table.  */
void isr_call(void){

    static unsigned int enc_state = 0;

    //Updates State to Previous State
    enc_state = enc_state << 2; 

    //Reads in New State. 
    enc_state = enc_state | ((PORTB & PINS_SEL_BIT_MASK) >> 5); //TODO: Make dynamic soon.

    enc_count = enc_count + transistion_table[enc_state & 0xF];

}

void _ISR _CNInterrupt(void){
    isr_call();
    _CNIF = 0;
}

int getTransistionTable(int index){
    return transistion_table[index];
}

int ENC_getEncoderCount(){
    return enc_count;
}

void ENC_setupEncoders(PORT_Channel port, PIN_Channel pinA, PIN_Channel pinB){
    PINS_SEL_BIT_MASK = (0x0001 << pinA) | (0x0001 << pinB);
    ANSELB = ~(PINS_SEL_BIT_MASK & ANSELB);
    
    //Interrupt Pin Selection
    IO_setPinIn(port, pinA);
    IO_setPinIn(port, pinB);
    CNENB = (PINS_SEL_BIT_MASK | CNENB); 
    
    //Interrupt Setup
    _CNIF = 0;
    _CNIP = 2;
    _CNIE = 1;
}

float ENC_getEncoder_Rads_per_sec(float delta_t_sec){
    long delta_ticks = (enc_count - prev_enc_count);
    prev_enc_count = enc_count;
    return (TICKS_TO_RADS_SF/delta_t_sec)*(float)delta_ticks; 
}

