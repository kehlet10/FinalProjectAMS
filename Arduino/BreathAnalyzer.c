/*
 * CFile1.c
 *
 * Created: 04-05-2022 21:12:00
 *  Author: Danie
 */ 



#include "BreathAnalyzer.h"

float sensorValue;
float sensor_volt;
float rs_gas;
float R0 = 1620; // Measurement made in capture.txt
float ratio;
float R2 = 1000;
int sensorResolution = 4095;
float voltageRange = 3.3;
double BAC;

void ADC_Init()
{
	// ADC Reference = 5V | Input = ADC0
	ADMUX = 0b01000000;
	// ADC Enabled | Free Running | No interrupts | Prescaler = 128
	ADCSRA = 0b11100111;
	ADCSRB = 0b00000000;
}

void breathAnalyzerInit()
{

	
	ADC_Init();
}

void checkR0Value()
{
	
	sensorValue = ADCW;
	sensor_volt = (float)sensorValue/sensorResolution*voltageRange; //Voltage range = 3.3V da det er fra vores controller board, Reso = 4095
	rs_gas = ((5.0*R2)/sensor_volt) - R2; //5V da det er på sensor boardet
	R0 = rs_gas / 60;
	//Serial.print("R0: ");
	//Serial.println(R0);
}

void BacLevel()
{
	//sensorValue = ADC level
	sensor_volt = (float)sensorValue/sensorResolution*voltageRange; //Voltage range = 3.3V da det er fra vores controller board, Reso = 4095
	rs_gas = ((5.0*R2)/sensor_volt) - R2; //5V da det er på sensor boardet
	ratio = rs_gas/R0;
	double x = 0.4*ratio;
	BAC = pow(x,-1.431); // g/ml
	char msg[32];
	int size_len = sprintf(msg, "Value is: %f\n", BAC);
	//Serial.print(msg);

}
