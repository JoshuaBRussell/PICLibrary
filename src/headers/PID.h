#ifndef _PID_H_
#define _PID_H_

/*----------------------------------------------------------------------------//
// PID Interface: Interface for the PID module. 
//----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------//
// PID Struct: Holds all the needed info for a specific PID instance. 
//----------------------------------------------------------------------------*/

typedef struct{

    //Paramaters
    float Kp;
    float Ki;
    float Kd;

    float setpoint;

    float deltaT;
    
    float totalError;
    float prevError;

    float out_max;
    float out_min;
} PID;


/*----------------------------------------------------------------------------//
// Functions for manipulating the PID instance
//----------------------------------------------------------------------------*/

//Initializes PID to a known state.
void PID_Init(PID* pid);

//---- Getter Functions ----//
//Gets the various PID coefficients
float PID_getKp(PID* pid);
float PID_getKi(PID* pid);
float PID_getKd(PID* pid);

//Gets the currently established setpoint
float PID_getSetpoint(PID* pid);

//---- Setter Functions ----//
//Sets the various values needed for the PID controller
void PID_setCoeff(PID* pid, float P, float I, float D);
void PID_setSetpoint(PID* pid, float setpoint);
void PID_setDeltaT(PID* pid, float deltaT);
void PID_setOutputLimits(PID* pid, float min, float max);

//Computes the output of the PID controller
float PID_Compute(PID* pid, float Input);
#endif // _PID_H_


