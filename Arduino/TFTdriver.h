/*
 * TFTdriver.h
 *
 * Created: 04-05-2022 20:55:46
 * Authors : Jonathan Bering & Daniel Damsgaard Kehlet
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLACK 0
#define RED 2
#define ORANGE 3
#define YELOOW 4
#define GREEN 5
#define BLUE 6
#define VIOLET 7
#define GRAY 8
#define WHITE 9
#define MAGENTA 10
#define LIME 11
#define BABY_POWDER 12
#define CYAN 13
#define LAVENDERBLUSH 14
#define BEIGE 15
//Variables
// Number Font

#ifndef TFT_DRIVER_H
#define TFT_DRIVER_H

//Methods
void DisplayInit(unsigned char backgroundColour, unsigned char textColour);
void DisplayOff();
void DisplayOn();
void SleepOut();
void MemoryAccessControl(unsigned char parameter);
void InterfacePixelFormatl (unsigned char parameter);
void WritePixel(unsigned char Red, unsigned char Blue, unsigned char Green);
void SetColumnAddress(unsigned int Start, unsigned int End);
void SetPageAddress(unsigned int Start, unsigned int End);
void MemoryWrite();
void setDisplayNumberFont(unsigned int X_Position, unsigned int Y_Position);
void setDisplayLetterFont(unsigned int X_Position, unsigned int Y_Position);
void setDisplayDotFont(unsigned int X_Position, unsigned int Y_Position);
void setDisplayPromilleFont(unsigned X_position, unsigned int Y_position, unsigned int ciphers);

unsigned int ClearScreen(unsigned char colour);
unsigned int clearPromille(unsigned int X_Position, unsigned int Y_Position, unsigned char colour, unsigned int ciphers);
unsigned int setpixelColour(unsigned int Colour);
unsigned int LetterToAscii(char Letter);

void WriteDot(unsigned int X_pos, unsigned int Y_pos, unsigned int Colour);
void WriteNumber(unsigned int X_pos, unsigned int Y_pos, unsigned int Colour, int NumberToWrite);
void WriteLetter(unsigned int X_pos, unsigned int Y_pos, unsigned int Colour, char LetterToWrite);
void WriteNumberFromADC(unsigned int X_Position,unsigned int Y_Position, unsigned int Colour, float num);

#endif
