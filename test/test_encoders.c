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

//----Test Encoder Functions----//
void test_Default_getEncoderCount(void){
    int val = getEncoderCount();
    TEST_ASSERT_EQUAL(0, val);
}

void test_setupEncoders(void){
    //TODO: Setup better test. (Simulation issues) 
    setupEncoders(0, 0, 0);
}

void test_getEncoderRads_sec(void){

    getEncoder_Rads_per_sec(0.01);
}




