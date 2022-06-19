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

#include "Engine.h"
#include "Light.h"
#include "Sound.h"

unsigned char mapNum = 0;

bool newPoint = false;

void reflectDetection(){
	mapNum++;
	newPoint = true;
	
	_delay_ms(300);
	EIFR = 0xFF;
	EIMSK |= 0b00000011;
}

ISR(INT0_vect) {
	EIMSK |= 0b00000000;
	reflectDetection();
}

ISR(INT1_vect) {
	EIMSK |= 0b00000000;
	reflectDetection();
}	


void init(){
	initEngine();
	initSound();
	initLight();
	sei();
	DDRB = 0xFF;
	EICRA = 0b00001111;
}

void run(){
     playTrack(0x01);
     while(isPlaying(0x01))
     {
     }
	
    lightOnOff(true);
    pwmEngine(20);
	
    mapNum = 0;
    EIFR = 0xFF;
    EIMSK |= 0b00000011;
	
	while(1){
		
		if(newPoint){
			newPoint=false;
			PORTB=mapNum;
			switch(mapNum){
				case 1:
					playTrack(0x02);
				break;
				
				case 2:
					playTrack(0x03);
					pwmAcceleration(2);
					pwmEngine(80); //lige f�r bakke
					_delay_ms(2000);
					pwmAcceleration(6);
					pwmEngine(20);
				break;
				
				case 3:
					playTrack(0x04);
					pwmAcceleration(5);
					pwmEngine(5);
				
					backLightIntensity(true);
					while(changingSpeed()){
					}
					_delay_ms(500);
					backLightIntensity(false);
				break;
				
				case 4:
					playTrack(0x05);
					pwmEngine(40);
					pwmAcceleration(3);
				break;
				
				case 5:
					playTrack(0x0C);
				break;
				
				case 6:
					playTrack(0x07);
				
					backLightIntensity(true);
					pwmEngine(0);
					while(changingSpeed()){
					}
					direction(false);
					pwmEngine(40);
					_delay_ms(500);
					backLightIntensity(false);
				break;
				
				case 7:
					playTrack(0x06);
				break;
				
				case 8:
					playTrack(0x08);
					backLightIntensity(true);
					pwmEngine(0);
					while(changingSpeed()){
					}
					direction(true);
					pwmEngine(50);
					_delay_ms(500);
					backLightIntensity(false);
				break;
				
				case 9:
					playTrack(0x03);
				break;
				
				case 10:
					playTrack(0x09);
					pwmAcceleration(4);
					pwmEngine(40);
					backLightIntensity(true);
					while(changingSpeed()){
					}
					_delay_ms(500);
					backLightIntensity(false);
				break;
				
				case 11:
					playTrack(0x0A);
					backLightIntensity(true);
					//pwmAcceleration(5);
					pwmEngine(0);
					while(changingSpeed()){
					}
					_delay_ms(500);
					backLightIntensity(false);
				
					while(isPlaying(0x0A))
					{
					}
					_delay_ms(500);
				
					playTrack(0x0B);
					while(isPlaying(0x0B))
					{
					}
					_delay_ms(1000);
				
					playTrack(0x0C);
					while(isPlaying(0x0C))
					{
					}
					_delay_ms(500);
				
					playTrack(0x0D);
					while(isPlaying(0x0D))
					{
					}
					_delay_ms(1000);
				
					playTrack(0x0E);
				break;
			}
		}
	}
}