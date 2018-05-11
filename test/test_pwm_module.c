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

// void test_set_OSCON(void)
// {
//     OC1R = 0x5000;
//     TEST_ASSERT_BITS(0xFFFF, 0x5000, OC1R); 
// }

void test_setHighTimeFloat(void)
{
    TEST_ASSERT_EQUAL(1000, getHighTimeFloat(6.0, 12.0, 2000));

    TEST_ASSERT_EQUAL(500, getHighTimeFloat(3.0, 12.0, 2000));

    TEST_ASSERT_EQUAL(250, getHighTimeFloat(1.5, 12.0, 2000));

    TEST_ASSERT_EQUAL(2000, getHighTimeFloat(6.0, 6.0, 2000));
}