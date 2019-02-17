#include "unity.h"
#include "encoders.h"
#include "xc.h"
#include "IO_Functions.h"

ENC my_ENC;
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

    ENC my_ENC;
    ENC_setupEncoders(&my_ENC,PORT_B, PIN_B0, PIN_B1, 64.0);
    //Disables correct ANALOG PINS?.
    TEST_ASSERT_BITS(PORTB_ANSEL_PIN_MASK,0xFFFC,ANSELB);
    //Correct pins are set as Inputs?
    TEST_ASSERT_BITS(0xFFFF, 0xFFFF, TRISB);
    //Change Pin Interrupt for selected port/pins is enabled
    TEST_ASSERT_BITS(PORTB_CNENB_PIN_MASK, 0xF003, CNENB);

    //Set to Default values
    //Port
    TEST_ASSERT_EQUAL(PORT_B, ENC_getENCPort(&my_ENC));
    //Pins
    TEST_ASSERT_EQUAL(PIN_B0, ENC_getENCPinA(&my_ENC));
    TEST_ASSERT_EQUAL(PIN_B1, ENC_getENCPinB(&my_ENC));
    //Prev Count
    TEST_ASSERT_EQUAL(0, ENC_getPrevENCCount(&my_ENC));
    //Current Count
    TEST_ASSERT_EQUAL(0, ENC_getENCCount(&my_ENC));
    //State
    TEST_ASSERT_EQUAL(0, ENC_getENCState(&my_ENC));
}

void test_getEncoderRads_sec(void){

    ENC_setupEncoders(&my_ENC,PORT_B, PIN_B0, PIN_B1, 64);
    ENC_getENCVel(0.01);
}

void test_isr_call_init_state01(void){

    ENC_setupEncoders(&my_ENC,PORT_B, PIN_B0, PIN_B1, 64);

    my_ENC.enc_state = 0x1;
    _CNIF = 1;

    int i = 0;
    for(i = 0; i < 50; i++){};//Adds a small delay so ISR has time to take effect
    
    TEST_ASSERT_EQUAL(4, my_ENC.enc_state);
    TEST_ASSERT_EQUAL(1, my_ENC.enc_count);


}

void test_isr_call_init_state10(void){

    ENC_setupEncoders(&my_ENC,PORT_B, PIN_B0, PIN_B1, 64.0);

    my_ENC.enc_state = 0x2;
    _CNIF = 1;

    int i = 0;
    for(i = 0; i < 50; i++){};//Adds a small delay so ISR has time to take effect
    
    TEST_ASSERT_EQUAL(8, my_ENC.enc_state);
    TEST_ASSERT_EQUAL(-1, my_ENC.enc_count);


}




