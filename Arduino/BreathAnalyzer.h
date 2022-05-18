/*
 * IncFile1.h
 *
 * Created: 04-05-2022 20:45:53
 *  Author: Danie
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>

#ifndef ADC
#define ADC

void breathAnalyzerInit();
 
void ADC_Init();
void breathAnalyzerInit();
void checkR0Value();
void BacLevel();

struct Breathalyzer {
	float _BAC;
	};



#endif /* INCFILE1_H_ */