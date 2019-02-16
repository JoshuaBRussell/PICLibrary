#include "unity.h"
#include "encoders.h"
#include "xc.h"
#include "IO_Functions.h"


void setUp(void)
{
}

void tearDown(void)
{
}

#define PORTB_ANSEL_PIN_MASK 0x010F
#define PORTB_CNENB_PIN_MASK 0xFFFF

//----Test Encoder Functions----//
void test_setupEncoders(void){
    ANSELB = 0xFFFF;
    CNENB = 0xF000;

    
    ENC_setupEncoders(PORT_B, PIN_B0, PIN_B1);
    //Disables correct ANALOG PINS?.
    TEST_ASSERT_BITS(PORTB_ANSEL_PIN_MASK,0xFFFC,ANSELB);
    //Correct pins are set as Inputs?
    TEST_ASSERT_BITS(0xFFFF, 0xFFFF, TRISB);
    //Change Pin Interrupt for selected port/pins is enabled
    TEST_ASSERT_BITS(PORTB_CNENB_PIN_MASK, 0xF003, CNENB);
}

void test_Default_getEncoderCount(void){
    int val = ENC_getEncoderCount();
    TEST_ASSERT_EQUAL(0, val);
}

void test_getEncoderRads_sec(void){

    ENC_getEncoder_Rads_per_sec(0.01);
}




