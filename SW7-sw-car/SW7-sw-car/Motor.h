/*
 * Motor.h
 *
 * Created: 5/3/2022 8:52:04 AM
 *  Author: Algorithm (Oliver G.)
 */ 

//#pragma once
//
//class Motor
//{
//public:
	//Motor();
	//
	//void initMotor();
	//void pwmMotor(unsigned char speed);
	//void direction(bool fwd);
	//void testMotor();
//
//private:
	//bool currentDir_; //true/false  fwd/bawd
	//unsigned char currentSpeed_; //from 1 to 100 procent
	//unsigned char desiredSpeed_; //from 1 to 100 procent
	//char accelleration_;
//
//};


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