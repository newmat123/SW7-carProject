/*
 * DriveControl.cpp
 *
 * Created: 10/05/2022 08.58.21
 *  Author: Nicklas
 */ 
#include <avr/io.h>
#include <stdlib.h>

#include "Motor.h"
#include "Light.h"
#include "Sound.h"


void init(){
	initMotor();
	initSound();
	initLight();
}

void run(){
	playTrack(0x02);
	
	while(isPlaying(0x02))
	{
	}
	
	lightOnOff(true);
	backLightIntensity(true);
	pwmMotor(70);
}