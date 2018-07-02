#include "unity.h"
#include "pwm_module.h"
#include "timer_functions.h"
#include "IO_Functions.h"
#include "xc.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_PWM_getPeriod(){
    PWM_Init(0, 2000);
    TEST_ASSERT_EQUAL_UINT16(2000, PWM_getPeriod());
    
}

// void test_set_OSCON(void)
// {
//     OC1R = 0x5000;
//     TEST_ASSERT_BITS(0xFFFF, 0x5000, OC1R); 
// }

