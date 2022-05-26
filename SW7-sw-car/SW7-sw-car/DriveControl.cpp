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

bool newPoint = false;



ISR(INT0_vect) {
	EIMSK |= 0b00000000;
	
 	mapNum++;
	newPoint = true;
	 
 	_delay_ms(500);
	EIFR = 0xFF;
 	EIMSK |= 0b00000011;
}

ISR(INT1_vect) {
	EIMSK |= 0b00000000;
	
	mapNum++;
	newPoint = true;
	
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
    playTrack(0x01);
    while(isPlaying(0x01))
    {
    }
	
    lightOnOff(true);
    pwmMotor(35);
	
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
				pwmMotor(80);
				break;
				
				case 3:
				playTrack(0x04);
				pwmAcceleration(10);
				pwmMotor(20);
				
				backLightIntensity(true);
				while(changingSpeed()){
				}
				_delay_ms(500);
				backLightIntensity(false);
				break;
				
				case 4:
				playTrack(0x05);
				pwmMotor(40);
				break;
				
				case 5:
				playTrack(0x0C);
				break;
				
				case 6:
				playTrack(0x07);
				
				backLightIntensity(true);
				pwmMotor(0);
				while(changingSpeed()){
				}
				direction(false);
				pwmMotor(40);
				_delay_ms(500);
				backLightIntensity(false);
				
				break;
				
				case 7:
				playTrack(0x06);
				break;
				
				case 8:
				playTrack(0x08);
				backLightIntensity(true);
				pwmMotor(0);
				while(changingSpeed()){
				}
				direction(true);
				pwmMotor(60);
				_delay_ms(500);
				backLightIntensity(false);
				break;
				
				case 9:
				playTrack(0x03);
				break;
				
				case 10:
				playTrack(0x09);
				pwmMotor(30);
				backLightIntensity(true);
				while(changingSpeed()){
				}
				_delay_ms(500);
				backLightIntensity(false);
				break;
				
				case 11:
				playTrack(0x0A);
				backLightIntensity(true);
				pwmAcceleration(30);
				pwmMotor(0);
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