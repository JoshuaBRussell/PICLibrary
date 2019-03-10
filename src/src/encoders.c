#include "encoders.h"
#include "stdbool.h"
#include "stdint.h"
#include "IO_Functions.h"
#include "xc.h"

struct ENC_obj{

    //Paramaters
    PORT_Channel port;
    PIN_Channel pinA;
    PIN_Channel pinB;

    volatile long prev_enc_count;
    volatile long enc_count;
    unsigned int enc_state;

    float TICKS_PER_REV;
    float TICKS_TO_RADS_SF;

};

static struct ENC_obj enc1;

static uint16_t PINS_SEL_BIT_MASK = 0x0003;


//Selects whether to increment/decrement the encoder count depending on the state change of the encoder. 
static int transistion_table[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

/* Represents the readings of the A/B lines as states.
// The previous state and current state are concatenated,  
// and the resulting value is used as an index for the transition table.  */
void isr_call(void){

    //Updates State to Previous State
    enc1.enc_state = enc1.enc_state << 2; 

    //Raw PORT reads of PORT for speed.
    uint16_t result = (PORTB >> (enc1.pinB));
    result &= 0x0003;

    //Reads in New State. 
    enc1.enc_state = enc1.enc_state | result;

    enc1.enc_count = enc1.enc_count + transistion_table[enc1.enc_state & 0xF];

}

void _ISR _CNInterrupt(void){
    isr_call();
    _CNIF = 0;
}

int getTransistionTable(int index){
    return transistion_table[index];
}

//Getters 
PORT_Channel ENC_getENCPort(ENC_Handle enc){
    return enc->port;
}

PIN_Channel ENC_getENCPinA(ENC_Handle enc){
    return enc->pinA;
}

PIN_Channel ENC_getENCPinB(ENC_Handle enc){
    return enc->pinB;
}

long ENC_getENCCount(ENC_Handle enc){
    return enc->enc_count;
}

long ENC_getPrevENCCount(ENC_Handle enc){
    return enc->prev_enc_count;
}

unsigned int ENC_getENCState(ENC_Handle enc){
    return enc->enc_state;
}

ENC_Handle ENC_setupEncoders(PORT_Channel port, PIN_Channel pinA, PIN_Channel pinB,
                       float TICKS_PER_REV){
    
    //Setup Struct
    enc1.port = port;
    enc1.pinA = pinA;
    enc1.pinB = pinB;

    enc1.prev_enc_count = 0;
    enc1.enc_count = 0;
    enc1.enc_state = 0;

    enc1.TICKS_PER_REV = TICKS_PER_REV;
    enc1.TICKS_TO_RADS_SF = (6.283185/TICKS_PER_REV);
    
    
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

    return &enc1;
}

float ENC_getENCVel(ENC_Handle enc, float delta_t_sec){
    long delta_ticks = (enc->enc_count - enc->prev_enc_count);
    enc->prev_enc_count = enc->enc_count;
    return (enc->TICKS_TO_RADS_SF/delta_t_sec)*(float)delta_ticks; 
}

