/*
 * Motor.cpp
 *
 * Created: 09/05/2022 10.53
 *  Author: nicklas
 */ 
#include <avr/io.h>
#include <stdbool.h>
#define F_CPU 16000000 //defines clock frekvens
#include <avr/interrupt.h>
#include "Motor.h"

//Variables
bool currentDir = true;         //determins the current dir true = fwd
unsigned char currentSpeed = 0; //determins the current speed
unsigned char desiredSpeed = 0; //used for acceleration
bool speedUp = true; 
unsigned char acceleration = 5;

ISR(TIMER3_OVF_vect){
	
	//controls the acceleration
	if (speedUp){
		if(desiredSpeed >= (currentSpeed+acceleration)){
			currentSpeed += acceleration;
		}else{
			currentSpeed = desiredSpeed;
		}
	}else{
		if(desiredSpeed <= (currentSpeed-acceleration)){
			currentSpeed -= acceleration;
			}else{
			currentSpeed = desiredSpeed;
		}
	}
	
	//sets the speed and dir
	int pwmSignal = currentSpeed * 10.2; // 100% = 1020
	if (!currentDir)
	{
		OCR1B = 0;
		OCR1A = pwmSignal;
	}
	else {
		OCR1A = 0;
		OCR1B = pwmSignal;
	}
	
	//stops timer interrupts
	if (desiredSpeed == currentSpeed){ 
		TIMSK3 |= 0b00000000;
	}
}

void initMotor(){
	TCCR1A = 0b10100011;
	TCCR1B = 0b00000001;
	
	TIMSK3 |= 0b00000000; //no interrupts
	TCCR3A = 0b00000000; //normal mode
	TCCR3B = 0b00000010; //prescaler
	
	OCR1A = 0;
	sei(); // skal i main
	
	currentDir = true;
	pwmMotor(0); //currentSpeed = 0  desiredSpeed = 0
	speedUp = true;
	acceleration = 5;
}


//TCNT3 = 65536 - 40535;
//TCNT3 = 65500;
//OCR3A = 40535;
void pwmMotor(unsigned char speed){
	if (speed <= 100 && speed >= 0){//checks for valid input
		if(currentSpeed != speed){
			if(currentSpeed < speed){
				speedUp = true;
			}else{
				speedUp = false;
			}
			desiredSpeed = speed;
			
			TIMSK3 |= 0b00000001;
		}
	}
}
	
void direction(bool fwd){
	if(currentSpeed == 0 && desiredSpeed == 0){ //stå bilen stille
		currentDir = fwd; //fwd true/false
	}else{ //else stop car, change dir and return to speed
		unsigned char oldSpeed = desiredSpeed;
		pwmMotor(0);
		while(currentSpeed != desiredSpeed)
		{}
		currentDir = fwd;
		pwmMotor(oldSpeed);
	}
}

void pwmAcceleration(unsigned char num){
	if(num <=100 && num >= 0){
		acceleration = num;
	}
}



void testMotor(){
	DDRA = 0;
	DDRB = 0xFF;

	PORTB = 0;

	while(1){

		if (~PINA & (1 << 0)){
			pwmMotor(0); //0%
		}
		if (~PINA & (1 << 1))
		{
			pwmMotor(25); //25%
		}
		if (~PINA & (1 << 2))
		{
			pwmMotor(50); //50%
		}
		if (~PINA & (1 << 3))
		{
			pwmMotor(75); //75%
		}
		if (~PINA & (1 << 4))
		{
			pwmMotor(100); //100%
		}
		if (~PINA & (1 << 5))
		{
			pwmAcceleration(10);
		}
		if (~PINA & (1 << 6))
		{
			pwmAcceleration(1);
		}
		
		if (~PINA & (1 << 7))
		{
			direction(!currentDir);
		}
	}
}



//#include <stdio.h>
//#include <stdlib.h>
//#include "Motor.h"
//using namespace std;
//
//Motor::Motor() {
	//currentDir_ = true;
	//currentSpeed_ = 0;
	//desiredSpeed_ = 0;
	//accelleration_ = 1;
	//speedUp_ = true;
//}
//
//Motor::ISR(TIMER0_OVF_vect){
	//
	////controls the accelleration
	//if (speedUp_){
		//if(desiredSpeed_ >= (currentSpeed_ + accelleration_)){
			//currentSpeed_ += accelleration_;
			//}else{
			//currentSpeed_ = desiredSpeed_;
		//}
		//}else{
		//if(desiredSpeed_ <= (currentSpeed_ - accelleration_)){
			//currentSpeed_ -= accelleration_;
			//}else{
			//currentSpeed_ = desiredSpeed_;
		//}
	//}
	//
	////sets the speed and dir
	//int pwmSignal = currentSpeed_ * 10.2; // 100% = 1020
	//if (!currentDir_)
	//{
		//OCR1B = 0;
		//OCR1A = pwmSignal;
	//}
	//else {
		//OCR1A = 0;
		//OCR1B = pwmSignal;
	//}
	//
	////stops timer interrupts
	//if (desiredSpeed_ == currentSpeed_){
		//TIMSK0 |= 0b00000000;
	//}
//}
//
//void Motor::initMotor() {
	//TCCR1A = 0b10100011;
	//TCCR1B = 0b00000001;
	//
	//OCR1A = 0;
	//sei(); // skal i main
//}
//
//void Motor::pwmMotor(unsigned char speed) {
	//if (speed <= 100 && speed >= 0){//checks for valid input
		//if(currentSpeed_ != speed && desiredSpeed_ == currentSpeed_){
			//if(currentSpeed_ < speed){
				//speedUp_ = true;
				//}else{
				//speedUp_ = false;
			//}
			//desiredSpeed_ = speed;
			//
			//TIMSK0 |= 0b00000001;
			//TCCR0A = 0b00000000;
			//TCCR0B = 0b00000101;
		//}
	//}
//}
//
//void Motor::direction(bool fwd) {
	//if(currentSpeed_ == 0 && desiredSpeed_ == 0){ //kan kun vende motoren ved at stå stille
		//currentDir_ = fwd; //fwd true/false
		//}else{ //else stop car, change dir and return to speed
		//unsigned char oldSpeed = desiredSpeed_;
		//pwmMotor(0);
		//while(currentSpeed_ != desiredSpeed_)
		//{}
		//currentDir_ = fwd;
		//pwmMotor(oldSpeed);
	//}
//}
//
//void Motor::testMotor() {
	//DDRA = 0;
	//DDRB = 0xFF;
//
	//PORTB = 0;
//
	//while(1){
//
		//if (~PINA & (1 << 0)){
			//pwmMotor(0); //0%
		//}
		//if (~PINA & (1 << 1))
		//{
			//pwmMotor(25); //25%
		//}
		//if (~PINA & (1 << 2))
		//{
			//pwmMotor(50); //50%
		//}
		//if (~PINA & (1 << 3))
		//{
			//pwmMotor(75); //75%
		//}
		//if (~PINA & (1 << 4))
		//{
			//pwmMotor(100); //100%
		//}
		//
		//if (~PINA & (1 << 7))
		//{
			//direction(!currentDir_);
		//}
	//}
//}