/*
 * main.c
 * 
 * Created: 04-05-2022 20:55:46
 * Authors : Jonathan Bering & Daniel Damsgaard Kehlet
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "UART.h"
#include "BreathAnalyzer.h"
#include "SPIdriver.h"
#include "SDdriver.h"
#include "ff.h"
#include "TFTdriver.h"
#include "diskio.h"

FATFS FatFs;		/* FatFs work area needed for each volume */
FIL Fil;			/* File object needed for each open file */

int main(void)
{
	// Setup of SD card 
	UINT bw;
	FRESULT fr;

	f_mount(&FatFs, "", 0);		/* Give a work area to the default drive */
	
	InitUART(UART0, 9600, 8,'A');
	
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
	
	fr = f_open(&Fil, "Log.txt", FA_WRITE | FA_CREATE_ALWAYS);	/* Create a file */
	if (fr == FR_OK) 
	{
		f_write(&Fil, "Det duer!\r\n", 11, &bw);	/* Write data to the file */
		fr = f_close(&Fil);	
								/* Close the file */
		if (fr == FR_OK && bw == 11) 
		{
		  SendString(UART0,"Der er skrevet til SD kortet");
		}
	}
  } 
}
