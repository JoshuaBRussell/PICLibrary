#include "unity.h"
#include "encoders.h"
#include "xc.h"


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




