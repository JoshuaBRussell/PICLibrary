#include "unity.h"

#include "xc.h"
#include "motor_driver.h"
#include "IO_Functions.h"
#include "pwm_module.h"
#include "timer_functions.h"

void setUp(void)
{
}

void tearDown(void)
{
}

uint16_t getPWM_High_Time_from_Float(float input, float max_input, uint16_t us_max_period){
    return ((uint16_t)((input/max_input) * (float)us_max_period) + 0.5);
}

void test_MOTOR_Init(void)
{
    MOTOR motor1;
    MOTOR_Init(&motor1, 1.0, 0, 0, 0);
}


void test_get_motor_direction_default(){
    MOTOR motor1;
    MOTOR_Init(&motor1, 1.0, 0, 0, 1);
    TEST_ASSERT_EQUAL(DIR_1, MOTOR_getDirection(&motor1));
    TEST_ASSERT_BITS(0xFFFF, 0x0001, LATA);
}

void test_set_motor_direction(){
    MOTOR motor1;
    MOTOR_Init(&motor1, 1.0, 0, 0, 1);

    MOTOR_setDirection(&motor1, DIR_2);
    TEST_ASSERT_EQUAL(DIR_2, MOTOR_getDirection(&motor1));
    TEST_ASSERT_BITS(0xFFFF, 0x0002, LATA);

    MOTOR_setDirection(&motor1, DIR_1);
    TEST_ASSERT_EQUAL(DIR_1, MOTOR_getDirection(&motor1));
    TEST_ASSERT_BITS(0xFFFF, 0x0001, LATA);
}

void test_set_motor_output(){
    MOTOR motor1;
    MOTOR_Init(&motor1, 12.0, 0, 0, 1);
    
    float motor_input = 6.0;
    MOTOR_setOutput(&motor1, motor_input);

    TEST_ASSERT_EQUAL(DIR_1, MOTOR_getDirection(&motor1));

    motor_input = -6.0;
    MOTOR_setOutput(&motor1, motor_input);

    TEST_ASSERT_EQUAL(DIR_2, MOTOR_getDirection(&motor1));
}
