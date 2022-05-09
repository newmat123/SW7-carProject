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

bool currentDir = true;
unsigned char currentSpeed = 0;
unsigned char desiredSpeed = 0;
bool speedUp = true;
char accelleration = 1; //global var

ISR(TIMER0_OVF_vect){
	
	//controls the accelleration
	if (speedUp){
		if(desiredSpeed >= (currentSpeed+accelleration)){
			currentSpeed += accelleration;
		}else{
			currentSpeed = desiredSpeed;
		}
	}else{
		if(desiredSpeed <= (currentSpeed-accelleration)){
			currentSpeed -= accelleration;
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
		TIMSK0 |= 0b00000000;
	}
}

void initMotor(){
	
	currentDir = true;
	currentSpeed = 0;
	desiredSpeed = 0;
	speedUp = true;
	accelleration = 1; //global var
	
	TCCR1A = 0b10100011;
	TCCR1B = 0b00000001;
	
	OCR1A = 0;
	sei(); // skal i main
}

void pwmMotor(unsigned char speed){
	if (speed <= 100 && speed >= 0){//checks for valid input
		if(currentSpeed != speed && desiredSpeed == currentSpeed){
			if(currentSpeed < speed){
				speedUp = true;
			}else{
				speedUp = false;
			}
			desiredSpeed = speed;
			
			TIMSK0 |= 0b00000001;
			TCCR0A = 0b00000000;
			TCCR0B = 0b00000101;
		}
	}
}
	
void direction(bool fwd){
	if(currentSpeed == 0 && desiredSpeed == 0){ //kan kun vende motoren ved at stå stille
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