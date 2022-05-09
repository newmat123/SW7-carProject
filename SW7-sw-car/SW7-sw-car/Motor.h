/*
 * Motor.h
 *
 * Created: 5/3/2022 8:52:04 AM
 *  Author: Algorithm (Oliver G.)
 */ 
#include <stdbool.h>

//Variables
extern bool currentDir; //true/false  fwd/bawd
extern unsigned char currentSpeed; //from 1 to 100 procent
extern unsigned char desiredSpeed; //from 1 to 100 procent
extern char accelleration; //use this to change acceleration

//Functions
void initMotor();
void pwmMotor(unsigned char speed);
void direction(bool fwd);

//test
void testMotor();