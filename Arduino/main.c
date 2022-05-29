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
#include <stdbool.h>

#include "UART.h"
#include "Breathalyzer.h"
#include "SPIdriver.h"
#include "SDdriver.h"
#include "Button.h"
#include "ff.h"
#include "TFTdriver.h"
#include "diskio.h"

FATFS FatFs;		/* FatFs work area needed for each volume */
FIL Fil;			/* File object needed for each open file */

int main(void)
{
	
	// ============= FOR DEBUGGING ============= //
	char debugMsg[50];
	char debugString[20];
	// ========================================= //
	
	///-main_init_start
	
	// Initialize UART0 (Baud Rate = 9600, 8 Databits, No Parity)
	InitUART(UART0, 9600, 8,'A');
	SendString(UART0, "UART Initialized\r\n");
	
	// Initialize Digital Pin 13 (= PB7) to input (Actually Pin 8-13 are all inputs now)
	InitButton(0);
	
	// Initialize the Breathalyzer/Gas Sensor
	breathalyzerInit();
	float BAC = 0;
	bool newMeasurement = false;
	SendString(UART0, "Breathalyzer Initialized\r\n");
	
	// Initialize the TFT Display
	DisplayInit(MAGENTA, BLACK);
	SendString(UART0, "TFT Display Initialized\r\n");

	// Setup of SD card
	uint16_t pressCount = 0;
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
 ///-main_init_stop
 
 ///-while_start
  while(1) 
  {
	
	while(readButtonState(7) != 0){ // Check if Pin 13 (= 7th Pin in PINB) is set
			  								
	    BAC = BacLevel();														// Get the current BAC Level
		
		if (newMeasurement == false)
		{
			pressCount++;
			
			fr = f_open(&Fil, "Datalog.txt", FA_WRITE | FA_OPEN_APPEND);			// Open the existing Datalog file
			
			if (fr == FR_OK)
			{
				char msg[100];														// String to store Datalogging msg.
				int btw;															// Size of string msg.
				
				btw = sprintf(msg, "// ==================== Measurement #%d ==================== //\r\n", pressCount);
				
				f_write(&Fil, msg, btw, &bw);										// Writes the msg onto the SD Card
				
				fr = f_close(&Fil);													// Closes the opened file
				
				if (fr == FR_OK && bw == btw)										// If it was successful, send a UART message.
				{
					SendString(UART0, msg);
				}
			}
		}
		
		if(BAC != 0){
			newMeasurement = true;
		}
	
		// ============= FOR DEBUGGING ============= //
		/*memset(debugMsg,'0', strlen(debugMsg));
		memset(debugString,'0', strlen(debugString));
	
		dtostrf(BAC, 3, 3, debugString);
		sprintf(debugMsg, "BAC Level is %6s\r\n", debugString);
		SendString(UART0, debugMsg);*/
		// ========================================= //
	
		fr = f_open(&Fil, "Datalog.txt", FA_WRITE | FA_OPEN_APPEND);			// Open the existing Datalog file
		
		if (fr == FR_OK)
		{
			char stringBAC[10];													// String used to store value of converted float
			char msg[50];														// String to store Datalogging msg.
			int btw;															// Size of string msg.
		
			dtostrf(BAC, 3, 3, stringBAC);
			btw = sprintf(msg, "BAC Level is %6s\r\n",stringBAC);
		
			f_write(&Fil, msg, btw, &bw);										// Writes the msg onto the SD Card
		
			fr = f_close(&Fil);													// Closes the opened file
		
			if (fr == FR_OK && bw == btw)										// If it was successful, send a UART message.
			{
				SendString(UART0, msg);
			}
		
		}
	}
	
	if(newMeasurement == true){
		/* Display new BAC value */
		WriteNumberFromADC(60, 100, BLACK, BAC);
		// Reset 
		newMeasurement = false;
				
		// ============= FOR DEBUGGING ============= //
		memset(debugMsg,'0', strlen(debugMsg));
		memset(debugString,'0', strlen(debugString));
	
		dtostrf(BAC, 3, 3, debugString);
		sprintf(debugMsg, "BAC Level is %6s\r\n", debugString);
		SendString(UART0, debugMsg);
		// ========================================= //
		
	}
  }
  ///-while_stop 
}
