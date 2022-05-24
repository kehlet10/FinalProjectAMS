/*
 * main.c
 * 
 * Created: 04-05-2022 20:55:46
 * Authors : Jonathan Bering & Daniel Damsgaard Kehlet
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "UART.h"
#include "Breathalyzer.h"
#include "SPIdriver.h"
#include "SDdriver.h"
#include "ff.h"
#include "TFTdriver.h"
#include "diskio.h"

const unsigned char Black = 0;
const unsigned char Red = 2;
const unsigned char Orange = 3;
const unsigned char Yellow = 4;
const unsigned char Green = 5;
const unsigned char Blue = 6;
const unsigned char Violet = 7;
const unsigned char Gray = 8;
const unsigned char White = 9;
const unsigned char Magenta = 10;
const unsigned char Lime = 11;
const unsigned char Baby_Powder = 12;
const unsigned char Cyan = 13;
const unsigned char Lavenderblush = 14;
const unsigned char Beige = 15;

FATFS FatFs;		/* FatFs work area needed for each volume */
FIL Fil;			/* File object needed for each open file */

int main(void)
{
	DDRB = 0; // Set Digital Pin 13 to input (Actually Pin 8-13 are all inputs now)
	PORTB = 0;
	
	// FOR DEBUGGING;
	char debugMsg[50];
	char debugString[20];
	
	InitUART(UART0, 9600, 8,'A');
	SendString(UART0, "UART Initialized\r\n");
	
	breathalyzerInit();
	//Breathalyzer BA_Inst;
	float BAC = 0;
	SendString(UART0, "Breathalyzer Initialized\r\n");
	
	// Initialize the display
	DisplayInit();
	SendString(UART0, "TFT Display Initialized\r\n");
	ClearScreen(White);
	WriteLetter(100,100, Black, 'A');
	// Setup of SD card
	UINT bw;
	FRESULT fr;
	f_mount(&FatFs, "", 0);											/* Give a work area to the default drive */
	
	fr = f_open(&Fil, "Datalog.txt", FA_WRITE | FA_CREATE_ALWAYS);	// Change to FA_CREATE_NEW to only create a new one when no file exists
	
	char msg[50];
	int btw = 0;
	btw = sprintf(msg, "Breathalyzer Datalogger!\r\n");
	
	if (fr == FR_OK) {
		f_write(&Fil, msg, btw, &bw);
		fr = f_close(&Fil);
		if (fr == FR_OK && bw == btw) {
			SendString(UART0,"Datalog.txt er oprettet!\r\n");
		}
	}
	float x = 1;
  while(1) // Check if Pin 13 (= 7th Pin in PINB) is set
  {
	
	if((PINB & 0b10000000) != 0){ // Check if Pin 13 (= 7th Pin in PINB) is set
		
		

		SendString(UART0, "PINB7 Button Pressed\r\n");
		SendString(UART0, "BLOW INTO THE SENSOR!!!!");
		//checkR0Value();														// Jsed first time the MQ-3 Sensor started up to get R0 value
		//BacLevel(&BA_Inst);													// Get the current BAC Level
	    BAC = BacLevel();
		/*DisplayOn();
		_delay_ms(1000);
		DisplayOff();
		_delay_ms(1000);*/
		_delay_ms(500);
	
		// === FOR DEBUGGING === //
		memset(debugMsg,'0', strlen(debugMsg));
		memset(debugString,'0', strlen(debugString));
	
		dtostrf(BAC, 3, 3, debugString);
		sprintf(debugMsg, "BAC Level is %6s\r\n", debugString);
		SendString(UART0, debugMsg);
		// ===================== //
	
		fr = f_open(&Fil, "Datalog.txt", FA_WRITE | FA_OPEN_APPEND);			// Open the existing Datalog file
		if (fr == FR_OK)
		{
			char stringBAC[10];													// String used to store value of converted float
			char msg[50];														// String to store Datalogging msg.
			int btw;															// Size of string msg.
		
			//dtostrf(BA_Inst._BAC, 3, 3, stringBAC);							// Convert float to string
			dtostrf(BAC, 3, 3, stringBAC);
			btw = sprintf(msg, "Your BAC Level is %6s %%\n", stringBAC);
			WriteNumberFromADC(60, 100, Magenta, BAC);
			f_write(&Fil, msg, btw, &bw);										// Writes the msg onto the SD Card
		
			fr = f_close(&Fil);													// Closes the opened file
		
			if (fr == FR_OK && bw == btw)										// If it was successful, send a UART message.
			{
				SendString(UART0, msg);
			}
		
		}
	}
  } 
}
