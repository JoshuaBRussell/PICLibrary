#include "unity.h"
#include "pwm_module.h"
#include "timer_functions.h"
#include "IO_Functions.h"
#include "xc.h"

void setUp(void)
{
    OC1CON1 = 0x0000;
    OC1R = 0x0000;
    OC1RS = 0x0000;
    OC1CON2 = 0x0000;

}

void tearDown(void)
{
}

void test_PWM_setHighTime(){
    PWM_Init(0, 2000);
    PWM_setHighTime(1000);
}

void test_PWM_setOCxCON1(){
    //Make sure it starts at default value
    TEST_ASSERT_EQUAL_HEX(0x0000, OC1CON1);

    PWM_setOCCON1(PWM_0, 0x0005); 
    TEST_ASSERT_EQUAL_HEX(0x0005, OC1CON1);

}

void test_PWM_setOCxCLK(){
    //Make sure it starts at default value
    TEST_ASSERT_BITS(0x1C00, 0x0000, OC1CON1);

    //Peripheral
    PWM_setOCCLK(PWM_0, OC_CLOCK_PERIPHERAL);
    TEST_ASSERT_BITS(0x1C00, 0x1C00, OC1CON1);

    //Timer2/Defalt
    PWM_setOCCLK(PWM_0, OC_CLOCK_TIMER_2);
    TEST_ASSERT_BITS(0x1C00, 0x0000, OC1CON1);

    //Timer3
    PWM_setOCCLK(PWM_0, OC_CLOCK_TIMER_3);
    TEST_ASSERT_BITS(0x1C00, 0x0400, OC1CON1);


}

void test_PWM_setOCxMode(){
    TEST_ASSERT_BITS(0x0007, 0x0000, OC1CON1);

    //Set to Edge Aligned
    PWM_setOCMode(PWM_0, OC_MODE_EDGE_PWM);
    TEST_ASSERT_BITS(0x0007, 0x0006, OC1CON1);

    //Set to Center Aligned
    PWM_setOCMode(PWM_0, OC_MODE_CENTER_PWM);
    TEST_ASSERT_BITS(0x0007, 0x0007, OC1CON1);
}

void test_PWM_setOCxR(){
    TEST_ASSERT_EQUAL(0x0000, OC1R);

    PWM_setOCR(PWM_0, 1000);
    TEST_ASSERT_EQUAL(1000, OC1R);

    PWM_setOCR(PWM_0, 1234);
    TEST_ASSERT_EQUAL(1234, OC1R);
}

void test_PWM_setOCRS(){
    TEST_ASSERT_EQUAL(0x0000, OC1RS);

    PWM_setOCRS(PWM_0, 1000);
    TEST_ASSERT_EQUAL(1000, OC1RS);

    PWM_setOCRS(PWM_0, 1234);
    TEST_ASSERT_EQUAL(1234, OC1RS);
}

void test_PWM_setOCTrig(){
    TEST_ASSERT_EQUAL(0x0000, OC1CON2);

    PWM_setOCTrig(PWM_0, OC_TRIG_TRIG);
    TEST_ASSERT_EQUAL(0x0080, OC1CON2);
    
    PWM_setOCTrig(PWM_0, OC_TRIG_SYNC);
    TEST_ASSERT_EQUAL(0x0000, OC1CON2);
}

void test_PWM_setSyncSel(){
    TEST_ASSERT_EQUAL(0x0000, OC1CON2);

    PWM_setOCSyncSel(PWM_0, OC_SYNC_SEL_OCxRS);
    TEST_ASSERT_EQUAL(0x0001F, OC1CON2);
}

void test_PWM_setScaledOutput(){
    OC1RS = 1000;
    PWM_setScaledOutput(PWM_0, 0.5);
    TEST_ASSERT_UINT16_WITHIN(5, 500, OC1R);
}