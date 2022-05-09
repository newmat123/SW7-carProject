/*
 * SW7-sw-car.cpp
 *
 * Created: 09/05/2022 13.59.57
 * Author : nicklas
 */ 

#include <avr/io.h>
#include "Motor.h"


int main(void)
{
	initMotor();
	direction(true);
	pwmMotor(0);
	testMotor();
    /* Replace with your application code */
    while (1) 
    {
    }
}

