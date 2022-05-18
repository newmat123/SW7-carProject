/*
 * Sound.cpp
 *
 * Created: 10/05/2022 08.56.09
 *  Author: Nicklas
 */ 

#include <avr/io.h>
#include <stdlib.h>
#define XTAL 16000000

void initSound(){
	//7E 06 00 00 (1E) FF DC EF  (1E)=30 max
	//baud mega 2560 = 115200
	// baud target 9600
	//1 stop bit
	//8 data bit
	// no paritet
	UCSR1A = 0b00100000;
	
	UCSR1B = 0b00011000;
	
	UCSR1C = 0b00000000;
	
	unsigned int baudRate = 9600;
	UBRR1 = (XTAL+(8*baudRate))/(16*baudRate)-1;
	
}

void playTrack(int trackNum){
	if(trackNum >= 1 && trackNum <= 1){
		//7E 03 00 00 (01) FF FC EF  (01) = track 1 op til 16 fx 0A = 10
		unsigned long data = 0x7E03000001FFFCEF;
		UDR1 = data;
		
	}
}

void stopTrack(){
	unsigned long data = 0x7E16000000FFEEEF;
	UDR1 = data;
}


void SendChar(char Tegn)
{
	while((UCSR1A & 0b00100000) == 0)
	{
	}
	UDR1 = Tegn;
}


void SendString(char* Streng)
{
	while (*Streng != 0)
	{
		SendChar(*Streng);
		
		Streng++;
	}
}

void SendInteger(unsigned long Tal)
{
	char array[7];
	itoa(Tal, array, 10);
	SendString(array);
}



void testSound(){
	DDRA = 0;
	DDRB = 0xFF;

	PORTB = 0;
	
	unsigned long data = 12;
	SendInteger(data);

	while(1){

		if (~PINA & (1 << 0)){
			unsigned long data = 0x7E16000000FFEEEF;
			SendInteger(data);
			//playTrack(1);
		}
		if (~PINA & (1 << 1))
		{
			stopTrack();
		}
		
	}
}