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

bool currentDir = false;
unsigned char currentSpeed = 0;
unsigned char desiredSpeed = 0;
bool speedUp = true;
char accelleration = 2; //global var

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


//
//using namespace std;
//
//Motor::Motor() {
	//TCCR1A = 0b10100011;
	//TCCR1B = 0b00000001;
	//
	//OCR1A = 0;
	//sei(); // skal i main
//}
//
//void Motor::pwmMotor(unsigned char speed) {
	//if (speed <= 100 && speed >= 0){//checks for valid input
		//if(currentSpeed != speed && desiredSpeed == currentSpeed){
			//if(currentSpeed < speed){
				//speedUp = true;
				//}else{
				//speedUp = false;
			//}
			//desiredSpeed = speed;
			//
			//TIMSK0 |= 0b00000001;
			//TCCR0A = 0b00000000;
			//TCCR0B = 0b00000101;
		//}
	//}
//}
//
//void Motor::direction(bool fwd) {
	//if(currentSpeed == 0 && desiredSpeed == 0){ //kan kun vende motoren ved at stå stille
		//currentDir = fwd; //fwd true/false
		//}else{ //else stop car, change dir and return to speed
		//unsigned char oldSpeed = desiredSpeed;
		//pwmMotor(0);
		//while(currentSpeed != desiredSpeed)
		//{}
		//currentDir = fwd;
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
			//direction(!currentDir);
		//}
	//}
//}