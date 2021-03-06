/*
 * Breathalyzer.c
 *
 * Created: 04-05-2022 20:55:46
 * Authors : Jonathan Bering & Daniel Damsgaard Kehlet
 */

#include "Breathalyzer.h"
#include "UART.h"
#include <stdio.h>
#include <stdlib.h>

float sensorValue;
float sensor_volt;
float rs_gas;
float R0 = 1620; // Measurement made in capture.txt
float ratio;
float R2 = 1000;
int adcResolution = 1023;
float voltageRef = 5;
double BAC;

void ADC_Init()
{
	// ADC Reference = 5V | Input = ADC0
	//ADMUX = 0b0100000;
	
	// ADC Reference = 5V | Input = ADC7
	ADMUX = 0b01000111;
	
	// ADC Enabled | Free Running | No interrupts | Prescaler = 128
	ADCSRA = 0b11100111;
	ADCSRB = 0b00000000;
}

void breathalyzerInit()
{	
	ADC_Init();
}

void checkR0Value()
{
	sensorValue = ADCW;
	sensor_volt = (float)sensorValue/adcResolution*voltageRef; //Voltage range = 3.3V da det er fra vores controller board, Resolution = 1023
	rs_gas = ((5.0*R2)/sensor_volt) - R2; //5V da det er p? sensor boardet
	R0 = rs_gas / 60;
}

///-bac_start
float BacLevel(){
	// Get ADC Value
	sensorValue = ADCW;
		
	// Recalculate into BAC
	sensor_volt = (float)sensorValue/adcResolution*voltageRef; //Voltage range = 5V from Mega2560, Resolution = 1023
	
	rs_gas = ((voltageRef*R2)/sensor_volt) - R2;
	ratio = rs_gas/R0;
	double x = 0.4*ratio;
	BAC = pow(x,-1.431); // mg/L
	BAC *= 10; 

	return BAC;
}
///-bac_stop