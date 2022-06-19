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
#include "Engine.h"

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

void initEngine(){
	DDRB = 0xFF;
	
	TCCR1A = 0b10100011;
	TCCR1B = 0b00000001;
	
	TIMSK3 |= 0b00000000; //no interrupts
	TCCR3A = 0b00000000; //normal mode
	TCCR3B = 0b00000010; //prescaler
	
	OCR1A = 0;
	
	currentDir = true;
	pwmEngine(0); //currentSpeed = 0  desiredSpeed = 0
	speedUp = true;
	acceleration = 5;
}

void pwmEngine(unsigned char speed){
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
	if(fwd != currentDir){
		if(currentSpeed == 0 && desiredSpeed == 0){ //stå bilen stille
			currentDir = fwd; //fwd true/false
		}else{ //else stop car, change dir and return to speed
			unsigned char oldSpeed = desiredSpeed;
			pwmEngine(0);
   			while(currentSpeed != desiredSpeed)
   			{}
			currentDir = fwd;
			pwmEngine(oldSpeed);
		}
	}
}

void pwmAcceleration(unsigned char num){
	if(num <=100 && num >= 0){
		acceleration = num;
	}
}

//måske fjernes igen idk
bool changingSpeed(){
	if(currentSpeed != desiredSpeed){
		return true;
	}else{
		return false;
	}
}


void testEngine(){
	DDRA = 0;

	while(1){

		if (~PINA & (1 << 0)){
			pwmEngine(0); //0%
		}
		if (~PINA & (1 << 1))
		{
			pwmEngine(25); //25%
		}
		if (~PINA & (1 << 2))
		{
			pwmEngine(50); //50%
		}
		if (~PINA & (1 << 3))
		{
			pwmEngine(75); //75%
		}
		if (~PINA & (1 << 4))
		{
			pwmEngine(100); //100%
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
