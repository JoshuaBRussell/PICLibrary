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

    
    ENC_Handle my_ENC = ENC_setupEncoders(PORT_B, PIN_B0, PIN_B1, 64.0);
    //Disables correct ANALOG PINS?.
    TEST_ASSERT_BITS(PORTB_ANSEL_PIN_MASK,0xFFFC,ANSELB);
    //Correct pins are set as Inputs?
    TEST_ASSERT_BITS(0xFFFF, 0xFFFF, TRISB);
    //Change Pin Interrupt for selected port/pins is enabled
    TEST_ASSERT_BITS(PORTB_CNENB_PIN_MASK, 0xF003, CNENB);

    //Set to Default values
    //Port
    TEST_ASSERT_EQUAL(PORT_B, ENC_getENCPort(my_ENC));
    //Pins
    TEST_ASSERT_EQUAL(PIN_B0, ENC_getENCPinA(my_ENC));
    TEST_ASSERT_EQUAL(PIN_B1, ENC_getENCPinB(my_ENC));
    //Prev Count
    TEST_ASSERT_EQUAL(0, ENC_getPrevENCCount(my_ENC));
    //Current Count
    TEST_ASSERT_EQUAL(0, ENC_getENCCount(my_ENC));
    //State
    TEST_ASSERT_EQUAL(0, ENC_getENCState(my_ENC));
}

void test_getEncoderRads_sec(void){

    ENC_Handle my_ENC = ENC_setupEncoders(PORT_B, PIN_B0, PIN_B1, 64.0);
    _CNIF = 0;
    ENC_getENCVel(my_ENC, 0.01);
}

