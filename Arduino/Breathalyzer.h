/*
 * Breathalyzer.h
 *
 * Created: 21-05-2022 11:49:39
 *  Author: jonat
 */ 


#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>

#ifndef BREATHALYZER_H_
#define BREATHALYZER_H_

void ADC_Init();
void breathalyzerInit();
void checkR0Value();
//void BacLevel(Breathalyzer BA_Inst);
float BacLevel();

/*typedef struct Breathalyzer{
	float _BAC;
} gasSensor;
*/

#endif /* BREATHALYZER_H_ */