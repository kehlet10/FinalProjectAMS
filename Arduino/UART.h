/*
 * UART.h
 *
 * Created: 04-05-2022 20:55:46
 * Authors : Jonathan Bering & Daniel Damsgaard Kehlet
 */


#ifndef UART_H
#define UART_H

// Memory mapping the base address of the UART registers
#define UART0 0xC0
#define UART1 0xC8
#define UART2 0xD0
#define UART3 0x130

void InitUART(unsigned int UART_adr, unsigned long BaudRate, unsigned char DataBit, char Parity);
unsigned char CharReady(unsigned int UART_adr);
char ReadChar(unsigned int UART_adr);
void SendChar(unsigned int UART_adr, char Tegn);
void SendString(unsigned int UART_adr, char* Streng);
void SendInteger(unsigned int UART_adr, int Tal);
/****************************************/

#endif /* UART_H_ */