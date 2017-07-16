#include "encoders.h"
#include "stdbool.h"
#include "SFR_Defines.h"

#define PINS_SEL_BIT_MASK 0x0003

static int enc_count = 0;
static int transistion_table[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};







int getEncoderCount(){
    return enc_count;
}

int getTransistionTable(int index){
    if(index > 15)
    {
        return 2;
    }
    return transistion_table[index];
}

void isr_call(void){

    static unsigned int enc_state = 1;

    enc_state = enc_state << 2; //Updates Old State to Previous State

    enc_state = enc_state | (PORTA & PINS_SEL_BIT_MASK); 

    enc_count = enc_count + transistion_table[enc_state & 0xF];

}

