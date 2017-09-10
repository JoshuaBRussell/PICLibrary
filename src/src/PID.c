#include "PID.h"


float getKp(PID* pid){
    return pid->Kp;
}

float getKi(PID* pid){
    return pid->Ki;
}

float getKd(PID* pid){
    return pid->Kd;
}

float getSetpoint(PID* pid){
    return pid->setpoint;
}

void setCoeff(PID* pid, float P, float I, float D){
    pid->Kp = P;
    pid->Ki = I;
    pid->Kd = D;
}

void setSetpoint(PID* pid, float setpoint){
    pid->setpoint = setpoint;
}

void setDeltaT(PID* pid, float deltaT){
    pid->deltaT = deltaT;
}

void PID_Init(PID* pid){

    pid->Kp = 0.0;
    pid->Ki = 0.0;
    pid->Kd = 0.0;

    pid->setpoint = 0.0;

    pid->deltaT = 0.0;

    pid->totalError = 0.0;
    pid->prevError = 0.0;

}

float Compute(PID* pid, float proc_val){
    float error = pid->setpoint - proc_val;    //Solve for the Error
    float dError = error - pid->prevError;     //Delta Error

    pid->prevError = error;                    
    pid->totalError = pid->totalError + pid->Ki * error;
    
    return pid->Kp*(error) + (pid->totalError) + pid->Kd*((dError)/pid->deltaT);   
}