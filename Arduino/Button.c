/*
 * Button.c
 *
 * Created: 24-05-2022 11:39:25
 *  Author: jonat
 */ 
#include "Button.h"

void InitButton(unsigned char pinNumber){
		
	DDRB = pinNumber;						// Initialize digital pins
	PORTB = 0;								// Reset PORTB pin states
}


int readButtonState(unsigned int pinNumber){
	return (PINB & (1 << pinNumber));
}
