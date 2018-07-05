#include "unity.h"
#include "PID.h"

void setUp(void)
{
}

void tearDown(void)
{
}

//---- Test Init Function ----//
void test_PID_Init(void){
    PID myPID;
    PID_Init(&myPID);
}
//---- Test Getter Functions ----//
void test_getKp_Default(void){
    PID myPID;
    PID_Init(&myPID);
    TEST_ASSERT_EQUAL(0.0, PID_getKp(&myPID));

}

void test_getKi_Default(void){
    PID myPID;
    PID_Init(&myPID);
    TEST_ASSERT_EQUAL(0.0, PID_getKi(&myPID));

}

void test_getKd_Default(void){
    PID myPID;
    PID_Init(&myPID);
    TEST_ASSERT_EQUAL(0.0, PID_getKd(&myPID));

}

void test_getSetpoint_Default(void){
    PID myPID;
    PID_Init(&myPID);
    TEST_ASSERT_EQUAL(0.0, PID_getSetpoint(&myPID));

}

//---- Test Setters ----//
void test_setCoeff(void){
    PID myPID;
    PID_Init(&myPID);
    float P = 2.5; 
    float I = 3.5;
    float D = 6.4;

    PID_setCoeff(&myPID, P, I, D);

    TEST_ASSERT_EQUAL(P, PID_getKp(&myPID));
    TEST_ASSERT_EQUAL(I, PID_getKi(&myPID));
    TEST_ASSERT_EQUAL(D, PID_getKd(&myPID));

}

void test_setSetpoint(void){
    PID myPID;
    PID_Init(&myPID);

    TEST_ASSERT_EQUAL_FLOAT(0.0, PID_getSetpoint(&myPID));

    PID_setSetpoint(&myPID, 1.0);
    TEST_ASSERT_EQUAL_FLOAT(1.0, PID_getSetpoint(&myPID));
}

//---- Test Various Configs ----//
void test_Compute_P_Only(void){
    float proc_val = 0.5;

    PID myPID;
    PID_Init(&myPID);
    PID_setCoeff(&myPID, 1.0, 0.0, 0.0);
    
    TEST_ASSERT_EQUAL_FLOAT(-0.5, PID_Compute(&myPID, proc_val));

    PID_setSetpoint(&myPID, 1.0);
    TEST_ASSERT_EQUAL_FLOAT(0.5, PID_Compute(&myPID, proc_val));

}

void test_Compute_I_Only(void){
    float proc_val = 0.5;
    
    PID myPID;
    PID_Init(&myPID);
    PID_setCoeff(&myPID, 0.0, 1.0, 0.0);
    PID_setDeltaT(&myPID, 1.0);
    
    TEST_ASSERT_EQUAL_FLOAT(-0.5, PID_Compute(&myPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(-1.0, PID_Compute(&myPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(-1.5, PID_Compute(&myPID, proc_val));

    PID aPID;
    PID_Init(&aPID);
    PID_setCoeff(&aPID, 0.0, 1.0, 0.0);
    PID_setDeltaT(&aPID, 1.0);
    PID_setSetpoint(&aPID, 1.0);
    
    TEST_ASSERT_EQUAL_FLOAT(0.5, PID_Compute(&aPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(1.0, PID_Compute(&aPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(1.5, PID_Compute(&aPID, proc_val));


}

void test_Compute_D_Only(void){
    float proc_val = 0.5;
    
    PID myPID;
    PID_Init(&myPID);
    PID_setCoeff(&myPID, 0.0, 0.0, 1.0);
    PID_setDeltaT(&myPID, 1.0);
    PID_setSetpoint(&myPID, 1.0);

    TEST_ASSERT_EQUAL_FLOAT(0.5, PID_Compute(&myPID, proc_val));

    proc_val = 0.75;
    TEST_ASSERT_EQUAL_FLOAT(-0.25, PID_Compute(&myPID, proc_val));

}

void test_Max_Integral_Limit(void){
    float proc_val = 0.5;

    //----Test Max Integral Output Limit----//
    PID aPID;
    PID_Init(&aPID);
    PID_setCoeff(&aPID, 0.0, 1.0, 0.0); //I term is only non-zero term -> Only Integral Tested
    PID_setDeltaT(&aPID, 1.0);
    PID_setSetpoint(&aPID, 1.0);

    PID_setOutputLimits(&aPID, 0.0, 1.5);
    
    //Integral Winds Up
    TEST_ASSERT_EQUAL_FLOAT(0.5, PID_Compute(&aPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(1.0, PID_Compute(&aPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(1.5, PID_Compute(&aPID, proc_val));

    //Integral is Limited
    TEST_ASSERT_EQUAL_FLOAT(1.5, PID_Compute(&aPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(1.5, PID_Compute(&aPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(1.5, PID_Compute(&aPID, proc_val));
 
}

void test_Min_Integral_Limit(){
    float proc_val = 0.5;

    PID myPID;
    PID_Init(&myPID);
    PID_setCoeff(&myPID, 0.0, 1.0, 0.0);  //I term is only non-zero term -> Only Integral Tested
    PID_setDeltaT(&myPID, 1.0);
    
    PID_setOutputLimits(&myPID, -1.5, 0.0);
    
    TEST_ASSERT_EQUAL_FLOAT(-0.5, PID_Compute(&myPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(-1.0, PID_Compute(&myPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(-1.5, PID_Compute(&myPID, proc_val));

    TEST_ASSERT_EQUAL_FLOAT(-1.5, PID_Compute(&myPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(-1.5, PID_Compute(&myPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(-1.5, PID_Compute(&myPID, proc_val));
}

void test_Max_Output_Limit(void){
    float proc_val = 0.5;

    //----Test Max Output Limit----//
    PID aPID;
    PID_Init(&aPID);
    PID_setCoeff(&aPID, 10.0, 0.0, 0.0);
    PID_setDeltaT(&aPID, 1.0);
    PID_setSetpoint(&aPID, 1.0);

    PID_setOutputLimits(&aPID, 0.0, 1.5);
    
    
    TEST_ASSERT_EQUAL_FLOAT(1.5, PID_Compute(&aPID, proc_val));
    
 
}

void test_Min_Output_Limit(){
    float proc_val = 1.0;

    PID myPID;
    PID_Init(&myPID);
    PID_setCoeff(&myPID, 1.0, 0.0, 0.0);
    PID_setDeltaT(&myPID, 1.0);
    PID_setSetpoint(&myPID, 0.5);
    
    PID_setOutputLimits(&myPID, 0.0, 1.0);
    
    TEST_ASSERT_EQUAL_FLOAT(0.0, PID_Compute(&myPID, proc_val));

}


