/*
 * Motor.h
 *
 * Created: 09/05/2022 10.53
 *  Author: nicklas
 */ 

#pragma once
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
	//bool speedUp_;
//
//};

//Variables
// extern bool currentDir; //true/false  fwd/bawd
// extern unsigned char currentSpeed; //from 1 to 100 procent
// extern unsigned char desiredSpeed; //from 1 to 100 procent
// extern char accelleration; //use this to change acceleration

#include <stdbool.h>

//Functions
void initMotor();
void pwmMotor(unsigned char speed);
void direction(bool fwd);
void pwmAcceleration(unsigned char num);

bool changingSpeed();

//test
void testMotor();