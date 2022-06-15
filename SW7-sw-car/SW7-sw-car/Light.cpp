/*
 * Light.cpp
 *
 * Created: 10-05-2022 12:14:20
 *  Author: morten
 Testet 19-05-2022: Virker korrekt
 */ 
#include <avr/io.h>
#include "Light.h"

void initLight(){
	//Tilfældig port som udgang til forlys
	DDRL = 0xFF;
	//Baglys. Benytter PORTH, da timer 4 på mega2560 (OC4A = PORTH, ben 3 | 6 på arduino) 
	DDRH = 0xFF;
	
	//Slukker lyset som standard
	PORTL = 0;
	PORTH = 0;	
	//Init timer
	// Mode = 3 (PWM, Phase Correct, 10 bit) IKKE FAST MODE
	// Set OC4A on match down counting / Clear OC4A on match up counting
	// Clock prescaler = 1
	TCCR4A = 0b10000011; // bit 0,1 PWM
	TCCR4B = 0b00000001; //PRESCALER bit 0
}

void lightOnOff(bool onOff) {
	if (onOff == true) {
		PORTL = (1<<7); //lightOnOff(true); sender 1 tal på PORTJ ben 7, 79
		OCR4A = 205; //BEN 3 PORTH, 15 på arduino	
	}
	else {
		PORTL = 0;
		OCR4A = 0;
	}	
}

void backLightIntensity(bool high) {
	if(high == true) {
		//Duty cycle 100%
		 OCR4A = 1023;
	} else {
		// Duty cycle 20% VED NORMAL
		// D = OCR/TOP. D = 20% OCR = ukendt(løses i CAS program) TOP(afhænger af mode) = 1023
		OCR4A = 205; //PORT E ben 3
	}
}