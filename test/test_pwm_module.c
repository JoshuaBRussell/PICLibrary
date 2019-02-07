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



void test_PWM_setHighTime(){
    PWM_Init(0, 2000);
    startPWM();
    PWM_setHighTime(1000);
}