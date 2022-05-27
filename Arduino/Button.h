/*
 * Button.h
 *
 * Created: 24-05-2022 11:39:37
 *  Author: jonat
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include <avr/io.h>

void InitButton(unsigned char);
int readButtonState(unsigned int);


#endif /* BUTTON_H_ */