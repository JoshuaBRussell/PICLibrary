#include "unity.h"
#include "pwm_module.h"
#include "timer_functions.h"
#include "IO_Functions.h"
#include "xc.h"

void setUp(void)
{
    OC1CON1 = 0x0000;

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
    PWM_setHighTime(1000);
}

void test_PWM_setOCxCON1(){
    //Make sure it starts at default value
    TEST_ASSERT_EQUAL_HEX(0x0000, OC1CON1);

    PWM_setOCxCON1(PWM_0, 0x0005); 
    TEST_ASSERT_EQUAL_HEX(0x0005, OC1CON1);

}

void test_PWM_setOCxCLK(){
    //Make sure it starts at default value
    TEST_ASSERT_BITS(0x1C00, 0x0000, OC1CON1);

    //Peripheral
    PWM_setOCxCLK(PWM_0, OCxCON1_TIMER_SEL_PERIPHERAL);
    TEST_ASSERT_BITS(0x1C00, 0x1C00, OC1CON1);

    //Timer2/Defalt
    PWM_setOCxCLK(PWM_0, OCxCON1_TIMER_SEL_TIMER2);
    TEST_ASSERT_BITS(0x1C00, 0x0000, OC1CON1);

    //Timer3
    PWM_setOCxCLK(PWM_0, OCxCON1_TIMER_SEL_TIMER3);
    TEST_ASSERT_BITS(0x1C00, 0x0400, OC1CON1);


}

void test_PWM_setOCxMode(){
    TEST_ASSERT_BITS(0x0007, 0x0000, OC1CON1);

    //Set to Edge Aligned
    PWM_setOCxMode(PWM_0, OCxCON1_MODE_SEL_EDGE_PWM);
    TEST_ASSERT_BITS(0x0007, 0x0006, OC1CON1);
}