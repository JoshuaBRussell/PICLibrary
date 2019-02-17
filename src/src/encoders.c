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
static bool isr_called = false;
static uint16_t PINS_SEL_BIT_MASK = 0x0003;

extern ENC my_ENC;

//Selects whether to increment/decrement the encoder count depending on the state change of the encoder. 
static int transistion_table[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

/* Represents the readings of the A/B lines as states.
// The previous state and current state are concatenated,  
// and the resulting value is used as an index for the transition table.  */
void isr_call(void){

    //Updates State to Previous State
    my_ENC.enc_state = my_ENC.enc_state << 2; 

    //Raw PORT reads of PORT for speed.
    uint16_t result = (PORTB >> (my_ENC.pinB));
    result &= 0x0003;

    //Reads in New State. 
    my_ENC.enc_state = my_ENC.enc_state | result;

    my_ENC.enc_count = my_ENC.enc_count + transistion_table[my_ENC.enc_state & 0xF];

}

bool isISRCalled(){
    return isr_called;
}

void _ISR _CNInterrupt(void){
    isr_call();
    isr_called = true;
    _CNIF = 0;
}

int getTransistionTable(int index){
    return transistion_table[index];
}

//Getters
PORT_Channel ENC_getENCPort(ENC* enc){
    return enc->port;
}

PIN_Channel ENC_getENCPinA(ENC* enc){
    return enc->pinA;
}

PIN_Channel ENC_getENCPinB(ENC* enc){
    return enc->pinB;
}

long ENC_getENCCount(ENC* enc){
    return enc->enc_count;
}

long ENC_getPrevENCCount(ENC* enc){
    return enc->prev_enc_count;
}

unsigned int ENC_getENCState(ENC* enc){
    return enc->enc_state;
}

void ENC_setupEncoders(ENC* enc_obj, PORT_Channel port, PIN_Channel pinA, PIN_Channel pinB,
                       float TICKS_PER_REV){
    
    //Setup Struct
    enc_obj->port = port;
    enc_obj->pinA = pinA;
    enc_obj->pinB = pinB;

    enc_obj->prev_enc_count = 0;
    enc_obj->enc_count = 0;
    enc_obj->enc_state = 0;

    enc_obj->TICKS_PER_REV = TICKS_PER_REV;
    enc_obj->TICKS_TO_RADS_SF = (6.283185/TICKS_PER_REV);
    
    
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

float ENC_getENCVel(float delta_t_sec){
    long delta_ticks = (my_ENC.enc_count - my_ENC.prev_enc_count);
    my_ENC.prev_enc_count = enc_count;
    return (my_ENC.TICKS_TO_RADS_SF/delta_t_sec)*(float)delta_ticks; 
}

