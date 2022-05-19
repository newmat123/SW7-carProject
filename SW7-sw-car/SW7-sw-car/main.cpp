/*
 * SW7-sw-car.cpp
 *
 * Created: 09/05/2022 13.59.57
 * Author : nicklas
 */ 

#include <avr/io.h>
#include "DriveControl.h"

int main(void)
{
//  	initMotor();
//  	direction(true);
//  	pwmMotor(0);
//  	testMotor();
	init();
	
    DDRA = 0;
    DDRB = 0xFF;

    PORTB = 0;
    
    while(1){
	    
	    if (~PINA & (1 << 0)){
		    
		    run();
	    }
    }
}

