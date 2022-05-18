/*
 * main.c
 * 
 * Created: 04-05-2022 20:55:46
 * Authors : Jonathan Bering & Daniel Damsgaard Kehlet
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "TFTdriver.h"
#include "BreathAnalyzer.h"
#include "UART.h"


int main(void)
{

	InitUART(UART0, 9600, 8);
	
	breathAnalyzerInit();
	// Initialize the display
	DisplayInit();
	// All pixels white (background)
	//FillRectangle(0,0,320,240,31,63,31);
	//// Draw red parts of danish flag
	//FillRectangle(0,140,100,100,31,0,0);
	//FillRectangle(0,0,100,100,31,0,0);
	//FillRectangle(140,0,320-140,100,31,0,0);
	//FillRectangle(140,140,320-140,100,31,0,0);
 
  while(1)
  {
	 checkR0Value();
	 BacLevel();
    DisplayOn();
	_delay_ms(1000);
    DisplayOff();
	_delay_ms(1000);
  } 
}
