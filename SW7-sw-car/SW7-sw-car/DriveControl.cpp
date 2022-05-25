/*
 * DriveControl.cpp
 *
 * Created: 10/05/2022 08.58.21
 *  Author: Nicklas
 */ 
#include <avr/io.h>
#include <stdlib.h>
#define F_CPU 16000000 //defines clock frekvens
#include <avr/interrupt.h>#include <util/delay.h>

#include "Motor.h"
#include "Light.h"
#include "Sound.h"

unsigned char mapNum = 0;

void drive(){
	mapNum++;
	PORTB=mapNum;
	
	switch(mapNum){
		case 2:
		//setMortor(80, motorAccelerration); // up in speed
		pwmMotor(80);
		break;
		
		case 3:
		//setMortor(40, motorAccelerration); //down in speed
		pwmMotor(20);
		backLightIntensity(true);
//  		while(changingSpeed()){
//  			//wait
//  		}
		//vent halt sekund
		//backLightIntensity(false);
		break;
		
		case 4:
		backLightIntensity(false);
		//setMortor(80, motorAccelerration); //up in speed
		pwmMotor(40);
		break;
		
		case 6:
		direction(false);//switch dir
		while(changingSpeed()){
		}
		
		break;
		
		case 8:
		direction(true);//switch dir
		pwmMotor(80);
		break;
		
		case 11:
		//setMortor(0, 8);
		pwmAcceleration(8);
		pwmMotor(0);
		backLightIntensity(true);
		break;
	}
}

ISR(INT0_vect) {
	
	EIMSK |= 0b00000000;
 	drive();
	 
 	_delay_ms(500);
	EIFR = 0xFF;
 	EIMSK |= 0b00000011;
}

ISR(INT1_vect) {
	EIMSK |= 0b00000000;
	drive();
	_delay_ms(500);
	EIFR = 0xFF;
	EIMSK |= 0b00000011;
}	


void init(){
	initMotor();
	initSound();
	initLight();
	sei();
	DDRB = 0xFF;
	EICRA = 0b00001111;
}

void run(){
    playTrack(0x02);
    
    while(isPlaying(0x02))
    {
    }
    lightOnOff(true);
    pwmMotor(20);
    
    mapNum = 0;
    EIFR = 0xFF;
    EIMSK |= 0b00000011;
	//testMotor();
}