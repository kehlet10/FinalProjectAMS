/*
 * TFTdriver.c
 *
 * Created: 04-05-2022 20:55:46
 * Authors : Jonathan Bering & Daniel Damsgaard Kehlet
 */
 
#include <avr/io.h>
#include <avr/cpufunc.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <string.h>
#include "TFTdriver.h"
#include "UART.h"
#include "fonts.h"

// Data port definitions:
#define DATA_PORT_HIGH PORTA
#define DATA_PORT_LOW  PORTC

// Control port definitions:
#define WR_PORT PORTG
#define WR_BIT 2
#define DC_PORT PORTD
#define DC_BIT  7  //"DC" signal is at the shield called RS
#define CS_PORT PORTG
#define CS_BIT  1
#define RST_PORT PORTG
#define RST_BIT 0

//Colour management
unsigned int Background_Colour;

unsigned char R, G, B;
unsigned char R_back, G_back, B_back;


#define Black_Out         WritePixel(0,0,0);
#define Red_Out           WritePixel(255,0,0);
#define Orange_Out        WritePixel(255,155,0);
#define Yellow_Out        WritePixel(255,255,0);
#define Green_Out         WritePixel(0,255,0);
#define Blue_Out          WritePixel(0,0,255);
#define Violet_Out        WritePixel(196,0,255);
#define Gray_Out          WritePixel(128,128,128);
#define White_Out         WritePixel(255,255,255);
#define Magenta_Out       WritePixel(255,0,255);
#define Lime_Out		  WritePixel(111,255,0);
#define Baby_Powder_Out   WritePixel(141,186,206);
#define Cyan_Out          WritePixel(0,255,255);
#define Lavenderblush_Out WritePixel(255,240,245);
#define Beige_Out         WritePixel(207,185,151);


// ILI 9341 data sheet, page 238
void WriteCommand(unsigned char command)
{
	
	DATA_PORT_LOW = command; //Data s?ttes
	
	DC_PORT &= ~(1<<DC_BIT); //Her sættes DC port til 0
	
	CS_PORT &= ~(1 << CS_BIT); //CSX s?ttes lavt
	
	WR_PORT &= ~(1 << WR_BIT); //WRX s?ttes lavt
	
	_NOP();

	WR_PORT |= (1<<WR_BIT);
	
	_NOP();
	
}

// ILI 9341 data sheet, page 238
void WriteData(unsigned int data)
{
	DATA_PORT_HIGH =  data >> 8;
	DATA_PORT_LOW = data; //Data s?ttes
	
	DC_PORT |= (1<< DC_BIT); //Her sættes DC port til 1 
	
	CS_PORT &= ~(1 << CS_BIT); //CSX s?ttes lavt
	WR_PORT &= ~(1 << WR_BIT); //WRX s?ttes lavt
	
	_NOP(); //twr0 > 15 nanosekunder
	
	WR_PORT |= (1 << WR_BIT);
	
	_NOP();
}

// PUBLIC FUNCTIONS ////////////////////////////////////////////////////////////

// Initializes (resets) the display
void DisplayInit(unsigned char colourBackground, unsigned char colourText)
{
	//Controlpins skal v?re input
	DDRG |= 0b00000111;
	DDRD |= 0b10000000;
	//Data pins skal v?re outputs
	DDRA = 0xFF;
	DDRC = 0xFF;
	
	PORTG |= 0b00000111;
	PORTD |= 0b10000000;
	
	RST_PORT &= ~(1<<RST_BIT);
	
	_delay_ms(500);
	
	RST_PORT |= (1<<RST_BIT);
	
	_delay_ms(130);
	
	SleepOut();

	DisplayOn();
	
	MemoryAccessControl(0b00001000); //Sets BGR bit high
	
	InterfacePixelFormat(0b00000101); //16 bits pr. pixel
	
	ClearScreen(colourBackground);
	
	WriteLetter(30,		290,	colourText, 'B');
	WriteLetter(45,		290,	colourText, 'r');
	WriteLetter(57,		290,	colourText, 'e');
	WriteLetter(73,		290,	colourText, 'a');
	WriteLetter(89,		290,	colourText, 't');
	WriteLetter(105,	290,	colourText, 'h');
	WriteLetter(121,	290,	colourText, 'a');
	WriteLetter(137,	290,	colourText, 'l');
	WriteLetter(152,	285,	colourText, 'y');
	WriteLetter(168,	290,	colourText, 'z');
	WriteLetter(184,	290,	colourText, 'e');
	WriteLetter(200,	290,	colourText, 'r');
	
	WriteLetter(60,		140,	colourText, 'P');
	WriteLetter(75,		140,	colourText, 'r');
	WriteLetter(87,		140,	colourText, 'o');
	WriteLetter(116,	140,	colourText, 'i');
	WriteLetter(104,	140,	colourText, 'm');
	WriteLetter(127,	140,	colourText, 'l');
	WriteLetter(139,	140,	colourText, 'l');
	WriteLetter(153,	140,	colourText, 'e');
	WriteLetter(167,	137,	colourText, ':');
	
}

void DisplayOff()
{
	WriteCommand(0x28);
}

void DisplayOn()
{
	
	WriteCommand(0x29);
}

void SleepOut()
{
	WriteCommand(0x11);
}

void MemoryAccessControl(unsigned char parameter)
{
	WriteCommand(0x36); //memory access
	WriteData(parameter); //sets BGR bit
}

void InterfacePixelFormat(unsigned char parameter)
{
	WriteCommand(0x3A);
	WriteData(parameter);
}

void MemoryWrite()
{
	WriteCommand(0x2C); //Transfers data from MicroController unit to frame memory. When command is accepted resets positions to setPageAdress and setColumnAddress positions
}

// Red 0-31, Green 0-63, Blue 0-31
void WritePixel(unsigned char Red, unsigned char Green, unsigned char Blue)
{
	unsigned int data = 0;
	data |= Red << 11;
	data |= Green << 5;
	data |= Blue;
	
	WriteData(data);
	
}

// Set Column Address (0-239), Start > End
void SetColumnAddress(unsigned int Start, unsigned int End)
{
	WriteCommand(0x2A);
	WriteData(Start >> 8);	//SC[15:8]
	WriteData(Start);		//SC[7:0}
	WriteData(End >> 8);	//EC[15:8]
	WriteData(End);			//EC[7:0]
}

// Set Page Address (0-319), Start > End
void SetPageAddress(unsigned int Start, unsigned int End)
{
	WriteCommand(0x2B);
	WriteData(Start >> 8);	//SC[15:8]
	WriteData(Start);		//SC[7:0}
	WriteData(End >> 8);	//EC[15:8]
	WriteData(End);			//EC[7:0]
	
}

void setDisplayNumberFont(unsigned int X_Position, unsigned int Y_Position) //S?tter page og column address s?ledes at det passer med font widt + font height. Der er lavet en funktion for hver font der bliver anvendt
{
	unsigned int Set_start_column = 0x00 | X_Position;
	unsigned int Set_start_row = 0x00 | Y_Position;

	unsigned int Set_end_column = Set_start_column + Number_Font_Width-1; //(bytes -1 bit) 8 pixels = 1 byte, 16 pixels = 2 bytes
	unsigned int Set_end_row = Set_start_row + Number_Font_Height;
	
	SetColumnAddress(Set_start_column, Set_end_column);
	
	SetPageAddress(Set_start_row, Set_end_row);

	MemoryWrite();
	
}

void setDisplayLetterFont(unsigned int X_Position, unsigned int Y_Position)
{
	unsigned int Set_start_column = 0x00 | X_Position;
	unsigned int Set_start_row = 0x00 | Y_Position;

	unsigned int Set_end_column = Set_start_column + Letter_Font_Width-1; //(bytes -1 bit) 8 pixels = 1 byte, 16 pixels = 2 bytes
	unsigned int Set_end_row = Set_start_row + Letter_Font_Height;
	
	SetColumnAddress(Set_start_column, Set_end_column);
	
	SetPageAddress(Set_start_row, Set_end_row);

	MemoryWrite();
	
}

void setDisplayDotFont(unsigned int X_Position, unsigned int Y_Position)
{
	unsigned int Set_start_column = 0x00 | X_Position;
	unsigned int Set_start_row = 0x00 | Y_Position;

	unsigned int Set_end_column = Set_start_column + Dot_Font_Width-1; //(bytes -1 bit) 8 pixels = 1 byte, 16 pixels = 2 bytes
	unsigned int Set_end_row = Set_start_row + Dot_Font_Height;
	
	SetColumnAddress(Set_start_column, Set_end_column);
	
	SetPageAddress(Set_start_row, Set_end_row);

	MemoryWrite();
	
}

void setDisplayPromilleFont(unsigned X_Position, unsigned int Y_Position, unsigned int ciphers)
{
	unsigned int Set_start_column = 0x00 | X_Position;
	unsigned int Set_start_row = 0x00 | Y_Position;

	unsigned int Set_end_column = Set_start_column + (Number_Font_Width-1)*(ciphers+1); //(bytes -1 bit) 8 pixels = 1 byte, 16 pixels = 2 bytes
	unsigned int Set_end_row = Set_start_row + Number_Font_Height;
	
	SetColumnAddress(Set_start_column, Set_end_column);
	
	SetPageAddress(Set_start_row, Set_end_row);

	MemoryWrite();

}

unsigned int clearPromille(unsigned int X_Position, unsigned int Y_Position, unsigned char colour, unsigned int ciphers)
{
	static long int i;
	Background_Colour = 0x00 | colour;
	
	setDisplayPromilleFont(X_Position, Y_Position, ciphers);

	WriteCommand(0x2C); //Write Memory Start

	switch (colour)  {

		case 0:     for(i=0;i<76800;i++){
			Black_Out;
		} break;
		case 2:     for(i=0;i<76800;i++){
			Red_Out;
		} break;
		case 3:     for(i=0;i<76800;i++){
			Orange_Out;
		} break;
		case 4:     for(i=0;i<76800;i++){
			Yellow_Out;
		} break;
		case 5:     for(i=0;i<76800;i++){
			Green_Out;
		} break;
		case 6:     for(i=0;i<76800;i++){
			Blue_Out;
		} break;
		case 7:     for(i=0;i<76800;i++){
			Violet_Out;
		} break;
		case 8:     for(i=0;i<76800;i++){
			Gray_Out;
		} break;
		case 9:     for(i=0;i<76800;i++){
			White_Out;
		} break;
		case 10:    for(i=0;i<76800;i++){
			Magenta_Out;
		} break;
		case 11:    for(i=0;i<76800;i++){
			Lime_Out;
		} break;
		case 12:    for(i=0;i<76800;i++){
			Baby_Powder_Out;
		} break;
		case 13:    for(i=0;i<76800;i++){
			Cyan_Out;
		} break;
		case 14:    for(i=0;i<76800;i++){
			Lavenderblush_Out;
		} break;
		case 15:    for(i=0;i<76800;i++){
			Beige_Out;
		} break;
		default:    for(i=0;i<76800;i++){
			Baby_Powder_Out;
		} break;
	}
	return Background_Colour;
}

unsigned int ClearScreen(unsigned char colour)
{
	static long int i;
	Background_Colour = 0x00 | colour;
	
	SetColumnAddress(0, 239);
	SetPageAddress(0, 319);
	WriteCommand(0x2C); //Write Memory Start

	switch (colour)  {

		case 0:     for(i=0;i<76800;i++){
			Black_Out;
		} break;
		case 2:     for(i=0;i<76800;i++){
			Red_Out;
		} break;
		case 3:     for(i=0;i<76800;i++){
			Orange_Out;
		} break;
		case 4:     for(i=0;i<76800;i++){
			Yellow_Out;
		} break;
		case 5:     for(i=0;i<76800;i++){
			Green_Out;
		} break;
		case 6:     for(i=0;i<76800;i++){
			Blue_Out;
		} break;
		case 7:     for(i=0;i<76800;i++){
			Violet_Out;
		} break;
		case 8:     for(i=0;i<76800;i++){
			Gray_Out;
		} break;
		case 9:     for(i=0;i<76800;i++){
			White_Out;
		} break;
		case 10:    for(i=0;i<76800;i++){
			Magenta_Out;
		} break;
		case 11:    for(i=0;i<76800;i++){
			Lime_Out;
		} break;
		case 12:    for(i=0;i<76800;i++){
			Baby_Powder_Out;
		} break;
		case 13:    for(i=0;i<76800;i++){
			Cyan_Out;
		} break;
		case 14:    for(i=0;i<76800;i++){
			Lavenderblush_Out;
		} break;
		case 15:    for(i=0;i<76800;i++){
			Beige_Out;
		} break;
		default:    for(i=0;i<76800;i++){
			Baby_Powder_Out;
		} break;
	}
	return Background_Colour;
}

unsigned int setpixelColour(unsigned int Colour)
{
	unsigned int colour = 0x00 | Colour;

	switch (colour)  {

		case 0:     R = 0; G = 0, B = 0;
		break;
		case 2:     R = 255; G = 0, B = 0;
		break;
		case 3:     R = 255; G = 155, B = 0;
		break;
		case 4:     R = 255; G = 255, B = 0;
		break;
		case 5:     R = 0; G = 255, B = 0;
		break;
		case 6:     R = 0; G = 0, B = 255;
		break;
		case 7:     R = 196; G = 0, B = 255;
		break;
		case 8:     R = 128; G = 128, B = 128;
		break;
		case 9:     R = 255; G = 255, B = 255;
		break;
		case 10:    R = 255; G = 0, B = 255;
		break;
		case 11:    R = 111; G = 255, B = 0;
		break;
		case 12:    R = 141; G = 186, B = 206;
		break;
		case 13:    R = 0; G = 255, B = 255;
		break;
		case 14:    R = 255; G = 240, B = 245;
		break;
		case 15:    R = 207; G = 185, B = 151;
		break;
		default:    R = 0; G = 0, B = 0;
		break;
	}

	switch (Background_Colour)  {

		case 0:     R_back = 0; G_back = 0, B_back = 0;
		break;
		case 2:     R_back = 255; G_back = 0, B_back = 0;
		break;
		case 3:     R_back = 255; G_back = 155, B_back = 0;
		break;
		case 4:     R_back = 255; G_back = 255, B_back = 0;
		break;
		case 5:     R_back = 0; G_back = 255, B_back = 0;
		break;
		case 6:     R_back = 0; G_back = 0, B_back = 255;
		break;
		case 7:     R_back = 196; G_back = 0, B_back = 255;
		break;
		case 8:     R_back = 128; G_back = 128, B_back = 128;
		break;
		case 9:     R_back = 255; G_back = 255, B_back = 255;
		break;
		case 10:    R_back = 255; G_back = 0, B_back = 255;
		break;
		case 11:    R_back = 111; G_back = 255, B_back = 0;
		break;
		case 12:    R_back = 141; G_back = 186, B_back = 206;
		break;
		case 13:    R_back = 0; G_back = 255, B_back = 255;
		break;
		case 14:    R_back = 255; G_back = 240, B_back = 245;
		break;
		case 15:    R_back = 207; G_back = 185, B_back = 151;
		break;
		default:    R_back = 0; G_back = 0, B_back = 0;
		break;
	}

	return colour;
	return Background_Colour;
	
}


//Numbers *********************************************************** Numbers *************************************************
void WriteNumber(unsigned int X_pos, unsigned int Y_pos, unsigned int Colour, int NumberToWrite)
{
	static unsigned char x=0;
	static unsigned char dataout=0;
	static unsigned int i=1;
	static unsigned int jj=0;
	
	setpixelColour(Colour);
	setDisplayNumberFont(X_pos,Y_pos);
	
	if(NumberToWrite == 0)
	{
		for (jj=Number_Font_Start; jj<Number_Font_Length_Bytes-1; jj++)
		{
			for (x=0; x<8; x++)
			{
				dataout = Number_Font[jj] &i;
				if (dataout >=1)
				{
					//Number zero
					WritePixel(R,G,B);
				}
				else
				{
					WritePixel(R_back,G_back,B_back);
				}
				i=i<<1;

				if (i>=256)
				{
					i=1;
				}
			}
		}
	}
	else
	{	//for (jj=Number_Font_Length_Bytes*(NumberToWrite+1)-1; jj>Number_Font_Length_Bytes*NumberToWrite; jj--)
		for (jj=Number_Font_Length_Bytes*NumberToWrite; jj<(Number_Font_Length_Bytes)*(NumberToWrite+1)-1; jj++)
		{
			for (x = 0; x < 8; x++){

				//dataout = Number_Font[jj] &i;
				dataout = (Number_Font[jj] & i);
				

				if (dataout >=1){
					//Rest
					WritePixel(R,G,B);
				} else
				{
				WritePixel(R_back,G_back,B_back); }

				i=i<<1;

				if (i>=256){
				i=1;}
			}
		}
	}
}


void WriteNumberFromADC(unsigned int X_Position, unsigned int Y_Position, unsigned int setColour, float num)
{
	unsigned int Font_Width;
	Font_Width = Number_Font_Width + Number_Font_Spacing;
	unsigned int posX;
	unsigned int i = 0;
	unsigned int tempIndex = 0;
	//unsigned int stringLength = 6;
	static unsigned char numberstring[6];
	
	// === FOR DEBUGGING === //
	char debugMsg[50];
	
	dtostrf(num, 3, 3, numberstring);     // Converts input unsigned long integer number to a string
	sprintf(debugMsg, "WriteNumber is %6s\r\n", numberstring);
	SendString(UART0, debugMsg );
	clearPromille(X_Position, Y_Position, Background_Colour, strlen(numberstring));
	
	for (i = 0; i < strlen(numberstring); i++)
	{

		if(numberstring[i] == 46)
		{
			posX = posX + Font_Width;
			SendString(UART0, "NumberString[i]");
			
		}
		else if (numberstring[i-1] == 46)
		{
			posX = posX + Number_Font_Spacing*8;
			X_Position = posX;
			SendString(UART0, "NumberString[i-1]");
			tempIndex = i;
		}
		else
		{
			posX = X_Position + Font_Width*(i-tempIndex);
			SendString(UART0, "Else");
		}
		
		switch (numberstring[i])  {  //units position
			case 46: WriteDot(posX, Y_Position, setColour);
			break;
			case 48:
			WriteNumber(posX,Y_Position, setColour, 0);
			break;
			case 49:
			WriteNumber(posX,Y_Position, setColour, 1);
			break;
			case 50:
			WriteNumber(posX,Y_Position, setColour, 2);
			break;
			case 51:
			WriteNumber(posX,Y_Position, setColour, 3);
			break;
			case 52:
			WriteNumber(posX,Y_Position, setColour, 4);
			break;
			case 53:
			WriteNumber(posX,Y_Position, setColour, 5);
			break;
			case 54:
			WriteNumber(posX,Y_Position, setColour, 6);
			break;
			case 55:
			WriteNumber(posX,Y_Position, setColour, 7);
			break;
			case 56:
			WriteNumber(posX,Y_Position, setColour, 8);
			break;
			case 57:
			WriteNumber(posX,Y_Position, setColour, 9);
			break;
			default:    break;
		}
	}


}


//Letters *********************************************************** Letters *************************************************

void WriteDot(unsigned int X_pos, unsigned int Y_pos, unsigned int Colour)
{
	static unsigned char x=0;
	static unsigned char dataout=0;
	static unsigned int i=1;
	static unsigned int jj=0;
	
	setpixelColour(Colour);
	setDisplayDotFont(X_pos,Y_pos);
	
	
	for (jj=Dot_Font_Start; jj<Dot_Font_Length_Bytes; jj++)
	{
		for (x=0; x<8; x++)
		{
			dataout = Dot_font[jj] &i;
			if (dataout >=1)
			{
				//Number zero
				WritePixel(R,G,B);
			}
			else
			{
				WritePixel(R_back,G_back,B_back);
			}
			i=i<<1;

			if (i>=256)
			{
				i=1;
			}
		}
	}
	
}

unsigned int AsciiToFontIndex(char Letter)
{
	switch(Letter){ // Returnerer det rigtige index for de forskellige bogstavers hexkode
		case 66:	return 1;	break;
		case 114:	return 2;	break;
		case 101:	return 3;	break;
		case 97:	return 4;	break;
		case 116:	return 5;	break;
		case 104:	return 6;	break;
		case 108:	return 7;	break;
		case 121:	return 8;	break;
		case 122:	return 9;	break;
		case 80:	return 10;	break;
		case 111:	return 11;	break;
		case 109:	return 12;	break;
		case 105:	return 13;	break;
		case 58:	return 14;	break;
		default: break;
	}
	
}

void WriteLetter(unsigned int X_pos, unsigned int Y_pos, unsigned int Colour, char LetterToWrite)
{
	static unsigned char x=0;
	static unsigned char dataout=0;
	static unsigned int i=1;
	static unsigned int jj=0;
	unsigned int LetterIndex = AsciiToFontIndex(LetterToWrite);
	
	// === FOR DEBUGGING === //
	char debugMsg[50];
	static unsigned char numberstring[6];
	dtostrf(LetterIndex, 3, 3, numberstring);     // Converts input unsigned long integer number to a string
	sprintf(debugMsg, "WriteLetter is %6s\r\n", numberstring);
	SendString(UART0, debugMsg );
	
	setpixelColour(Colour);
	setDisplayLetterFont(X_pos,Y_pos);
	
	if(LetterIndex == 1) //Index 1 = start ved 0 ellers start ved index -1. Derved f?r den fat i den rigtige hex kode inde fra Letter_font arrayet
	{
		for (jj=Letter_Font_Start; jj<Letter_Font_Length_Bytes-1; jj++)
		{
			for (x=0; x<8; x++)
			{
				dataout = Letter_Font[jj] &i;
				if (dataout >=1)
				{
					WritePixel(R,G,B);
				}
				else
				{
					WritePixel(R_back,G_back,B_back);
				}
				i=i<<1;

				if (i>=256)
				{
					i=1;
				}
			}
		}
	}
	else
	{	//for (jj=Number_Font_Length_Bytes*(NumberToWrite+1)-1; jj>Number_Font_Length_Bytes*NumberToWrite; jj--)
		for (jj=Letter_Font_Length_Bytes*(LetterIndex-1); jj<(Letter_Font_Length_Bytes*LetterIndex)-1; jj++)
		{
			for (x = 0; x < 8; x++){
				
				dataout = (Letter_Font[jj] & i);
				
				if (dataout >=1){
					//Rest
					WritePixel(R,G,B);
				} else
				{
				WritePixel(R_back,G_back,B_back); }

				i=i<<1;

				if (i>=256){
				i=1;}
			}
		}
	}
}