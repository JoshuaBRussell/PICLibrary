#include "unity.h"
#include "pwm_module.h"
#include "xc.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_set_OSCON(void)
{
    OC1R = 0x5000;
    TEST_ASSERT_BITS(0xFFFF, 0x5000, OC1R); 
}
