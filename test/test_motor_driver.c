#include "unity.h"

#include "xc.h"
#include "motor_driver.h"
#include "IO_Functions.h"

void setUp(void)
{
}

void tearDown(void)
{
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
    MOTOR_setOutput(6.0);
}