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
	init();
    DDRA = 0;
    
    while(1){
	    if (~PINA & (1 << 7)){
		    run();
	    }
    }
}

