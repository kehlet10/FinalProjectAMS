/************************************************************
  File name: "TFTdriver.c"

  Driver for "ITDB02 320 x 240 TFT display module, Version 2"
  mounted at "ITDB02 Arduino Mega2560 Shield".
  Display controller = ILI 9341.
  
  Max. uC clock frequency = 16 MHz (Tclk = 62,5 ns)

  Connections:
  DB15-DB8:   PORT A
  DB7-DB0:    PORT C

  RESETx:     PORT G, bit 0
  CSx:        PORT G, bit 1
  WRx:        PORT G, bit 2
  RS (=D/Cx): PORT D, bit 7

  Henning Hargaard, February 15, 2018
************************************************************/  

//Variables
// Number Font

#ifndef TFT_DRIVER_H
#define TFT_DRIVER_H

//Methods
void DisplayInit();
void DisplayOff();
void DisplayOn();
void SleepOut();
void MemoryAccessControl(unsigned char parameter);
void InterfacePixelFormat(unsigned char parameter);
void WritePixel(unsigned char Red, unsigned char Blue, unsigned char Green);
void SetColumnAddress(unsigned int Start, unsigned int End);
void SetPageAddress(unsigned int Start, unsigned int End);
void MemoryWrite();
void setDisplayNumberFont(unsigned int X_Position, unsigned int Y_Position);
unsigned int ClearScreen(unsigned char colour);
unsigned int setpixelColour(unsigned int Colour);

void WriteNumber(unsigned int X_pos, unsigned int Y_pos, unsigned int Colour, int NumberToWrite);
void WriteLetter(unsigned int X_pos, unsigned int Y_pos, unsigned int Colour, char LetterToWrite);
void WriteNumberFromADC(unsigned int X_Position,unsigned int Y_Position, unsigned int Colour, float num);

#endif
