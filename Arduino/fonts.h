/*
 * fonts.h
 *
 * Created: 25-05-2022 12:22:33
 *  Author: Danie
 */ 


#ifndef FONTS_H_
#define FONTS_H_

//Fonts

const unsigned short Number_Font[] = { // 16x21 = 315/8 = 40 bytes
	0x00,0x7E,0x00,0xC0,0xFF,0x03,0xE0,0xFF,0x07,0xF0,0xFF,0x0F,0xF0,0xC3,0x0F,0xF8,0x00,0x1F,0xF8,0x00,0x1F,0x7C,0x00,0x3E,0x7C,0x00,0x3E,0x7C,0x00,0x3E,0x3C,0x00,0x3C,0x3E,0x00,0x7C,0x3E,0x00,0x7C,0x3E,0x00,0x7C,0x3E,0x00,0x7C,0x3E,0x00,0x7C,0x3E,0x00,0x7C,0x3E,0x00,0x7C,0x3E,0x00,0x7C,0x3E,0x00,0x7C,0x3E,0x00,0x7C,0x3E,0x00,0x7C,0x3E,0x00,0x7C,0x3E,0x00,0x7C,0x3E,0x00,0x7C,0x3E,0x00,0x7C,0x3C,0x00,0x3C,0x7C,0x00,0x3E,0x7C,0x00,0x3E,0x7C,0x00,0x3E,0xF8,0x00,0x1F,0xF8,0x00,0x1F,0xF0,0xC3,0x0F,0xF0,0xFF,0x0F,0xE0,0xFF,0x07,0xC0,0xFF,0x03,0x00,0x7E,0x00, // Code for char num 48
	0x00,0x00,0x00,0xE0,0xFF,0x3F,0xE0,0xFF,0x3F,0xE0,0xFF,0x3F,0xE0,0xFF,0x3F,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0xE0,0xFF,0x00,0xE0,0xFF,0x00,0xE0,0xFF,0x00,0x00,0xFE,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF0,0x00,0x00,0xF0,0x00,0x00,0x00,0x00, // Code for char num 49
	0x00,0x00,0x00,0xFC,0xFF,0x7F,0xFC,0xFF,0x7F,0xFC,0xFF,0x7F,0xFC,0xFF,0x7F,0x7C,0x00,0x00,0xF8,0x00,0x00,0xF0,0x01,0x00,0xE0,0x03,0x00,0xC0,0x07,0x00,0x80,0x0F,0x00,0x00,0x1F,0x00,0x00,0x3E,0x00,0x00,0x7E,0x00,0x00,0xFC,0x00,0x00,0xF8,0x01,0x00,0xF0,0x03,0x00,0xE0,0x03,0x00,0xC0,0x07,0x00,0xC0,0x0F,0x00,0x80,0x0F,0x00,0x00,0x1F,0x00,0x00,0x1F,0x00,0x00,0x3F,0x00,0x00,0x3E,0x00,0x00,0x3E,0x00,0x00,0x3E,0x00,0x00,0x3E,0x00,0x00,0x3E,0x00,0x00,0x3E,0x08,0x00,0x3F,0x38,0x80,0x1F,0xF8,0xC0,0x1F,0xF8,0xFF,0x0F,0xF8,0xFF,0x07,0xF0,0xFF,0x03,0x00,0xFF,0x00, // Code for char num 50
	0xC0,0x3F,0x00,0xFC,0xFF,0x01,0xFE,0xFF,0x03,0xFE,0xFF,0x07,0x7E,0xE0,0x0F,0x0E,0x80,0x1F,0x02,0x00,0x1F,0x00,0x00,0x1F,0x00,0x00,0x3E,0x00,0x00,0x3E,0x00,0x00,0x3E,0x00,0x00,0x3E,0x00,0x00,0x3E,0x00,0x00,0x3E,0x00,0x00,0x3E,0x00,0x00,0x1F,0x00,0x80,0x1F,0x00,0xC0,0x0F,0x00,0xFF,0x07,0x00,0xFF,0x01,0x00,0x7F,0x00,0x00,0xFF,0x01,0x00,0xF0,0x07,0x00,0xC0,0x07,0x00,0x80,0x0F,0x00,0x00,0x0F,0x00,0x00,0x1F,0x00,0x00,0x1F,0x00,0x00,0x1F,0x00,0x00,0x1F,0x04,0x80,0x1F,0x1C,0x80,0x1F,0x7C,0xE0,0x0F,0xFC,0xFF,0x07,0xFC,0xFF,0x07,0xF8,0xFF,0x01,0x80,0x7F,0x00, // Code for char num 51
	0x00,0x00,0x00,0x00,0x80,0x0F,0x00,0x80,0x0F,0x00,0x80,0x0F,0x00,0x80,0x0F,0x00,0x80,0x0F,0x00,0x80,0x0F,0x00,0x80,0x0F,0x00,0x80,0x0F,0x00,0x80,0x0F,0x00,0x80,0x0F,0x00,0x80,0x0F,0x00,0x80,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x0F,0x80,0x0F,0x1F,0x80,0x0F,0x3E,0x80,0x0F,0x7C,0x80,0x0F,0xF8,0x80,0x0F,0xF0,0x81,0x0F,0xE0,0x81,0x0F,0xE0,0x83,0x0F,0xC0,0x87,0x0F,0x80,0x8F,0x0F,0x00,0x9F,0x0F,0x00,0xBE,0x0F,0x00,0xFC,0x0F,0x00,0xF8,0x0F,0x00,0xF8,0x0F,0x00,0xF0,0x0F,0x00,0xE0,0x0F,0x00,0xC0,0x0F,0x00,0x80,0x0F,0x00,0x00,0x00, // Code for char num 52
	0x80,0x7F,0x00,0xF8,0xFF,0x01,0xFC,0xFF,0x07,0xFC,0xFF,0x0F,0xFC,0xC0,0x1F,0x1C,0x00,0x1F,0x04,0x00,0x3F,0x00,0x00,0x3E,0x00,0x00,0x7E,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0x7E,0x00,0x00,0x3E,0x00,0x00,0x3F,0x18,0xC0,0x1F,0xF8,0xFF,0x1F,0xF8,0xFF,0x0F,0xF8,0xFF,0x03,0xF8,0xFF,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0xFF,0x7F,0xF8,0xFF,0x7F,0xF8,0xFF,0x7F,0xF8,0xFF,0x7F,0x00,0x00,0x00, // Code for char num 53
	0x00,0xFE,0x00,0x80,0xFF,0x03,0xC0,0xFF,0x0F,0xE0,0xFF,0x1F,0xF0,0x83,0x3F,0xF8,0x01,0x3E,0xF8,0x00,0x7C,0x7C,0x00,0x7C,0x7C,0x00,0xF8,0x7C,0x00,0xF8,0x3C,0x00,0xF8,0x3E,0x00,0xF8,0x3E,0x00,0xF8,0x3E,0x00,0xF8,0x3E,0x00,0xF8,0x3E,0x00,0xFC,0x3E,0x00,0x7C,0x7E,0x00,0x7E,0xFE,0x01,0x3F,0xFE,0xFF,0x3F,0xFE,0xFF,0x1F,0x3E,0xFF,0x07,0x3E,0xFC,0x01,0x3C,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0xF0,0x01,0x00,0xF0,0x03,0x00,0xE0,0x07,0x00,0xC0,0x1F,0x10,0x80,0xFF,0x1F,0x00,0xFF,0x1F,0x00,0xFC,0x1F,0x00,0xE0,0x1F, // Code for char num 54
	0x00,0x00,0x00,0xF8,0x01,0x00,0xF0,0x01,0x00,0xF0,0x03,0x00,0xE0,0x03,0x00,0xE0,0x07,0x00,0xC0,0x07,0x00,0xC0,0x0F,0x00,0x80,0x0F,0x00,0x80,0x1F,0x00,0x00,0x1F,0x00,0x00,0x3F,0x00,0x00,0x3E,0x00,0x00,0x7E,0x00,0x00,0x7C,0x00,0x00,0xFC,0x00,0x00,0xF8,0x00,0x00,0xF8,0x01,0x00,0xF8,0x01,0x00,0xF0,0x01,0x00,0xF0,0x03,0x00,0xE0,0x03,0x00,0xE0,0x07,0x00,0xC0,0x07,0x00,0xC0,0x0F,0x00,0x80,0x0F,0x00,0x80,0x1F,0x00,0x00,0x1F,0x00,0x00,0x3F,0x00,0x00,0x3E,0x00,0x00,0x7E,0x00,0x00,0x7C,0xFE,0xFF,0x7F,0xFE,0xFF,0x7F,0xFE,0xFF,0x7F,0xFE,0xFF,0x7F,0x00,0x00,0x00, // Code for char num 55
	0x00,0xFE,0x00,0xC0,0xFF,0x07,0xE0,0xFF,0x0F,0xF0,0xFF,0x1F,0xF8,0x83,0x3F,0xFC,0x00,0x7E,0x7C,0x00,0x7C,0x7E,0x00,0xFC,0x3E,0x00,0xF8,0x3E,0x00,0xF8,0x3E,0x00,0xF8,0x3E,0x00,0xF8,0x3E,0x00,0xF8,0x3E,0x00,0xFC,0x7C,0x00,0x7C,0x7C,0x00,0x7F,0xF8,0x80,0x3F,0xF0,0xF1,0x1F,0xE0,0xFF,0x0F,0x80,0xFF,0x03,0xC0,0xFF,0x07,0xE0,0x1F,0x0F,0xF0,0x07,0x1E,0xF8,0x03,0x3E,0xF8,0x00,0x3C,0xFC,0x00,0x7C,0x7C,0x00,0x7C,0x7C,0x00,0x7C,0x7C,0x00,0x7C,0x7C,0x00,0x7C,0xFC,0x00,0x7E,0xF8,0x00,0x3E,0xF8,0x83,0x3F,0xF0,0xFF,0x1F,0xE0,0xFF,0x0F,0x80,0xFF,0x07,0x00,0xFE,0x00, // Code for char num 56
	0xF0,0x1F,0x00,0xF0,0x7F,0x00,0xF0,0xFF,0x01,0xF0,0xFF,0x03,0x10,0xF0,0x07,0x00,0xC0,0x0F,0x00,0x80,0x1F,0x00,0x00,0x1F,0x00,0x00,0x3E,0x00,0x00,0x3E,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0x78,0x00,0x7F,0x78,0xC0,0xFF,0xF9,0xF0,0xFF,0xFF,0xF8,0xFF,0xFF,0xF8,0x03,0xFF,0xFC,0x00,0xFC,0x7C,0x00,0xF8,0x7E,0x00,0xF8,0x3E,0x00,0xF8,0x3E,0x00,0xF8,0x3E,0x00,0xF8,0x3E,0x00,0xF8,0x3E,0x00,0xF8,0x3E,0x00,0x7C,0x3E,0x00,0x7C,0x7C,0x00,0x7C,0x7C,0x00,0x3E,0xF8,0x00,0x3F,0xF8,0x83,0x1F,0xF0,0xFF,0x0F,0xE0,0xFF,0x07,0x80,0xFF,0x03,0x00,0xFE,0x00 // Code for char num 57
};

const unsigned char Number_Font_Start = 0;
const unsigned char Number_Font_Length_Bytes = 111;
const unsigned char Number_Font_Width = 24;      // full bytes of pixels   8,16,24 etc
const unsigned char Number_Font_Height = 37	;
const unsigned char Number_Font_Spacing = 1;


const unsigned short Dot_font[] = {
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF                                          // Code for char num 46                                                               // Code for char num 46
};

const unsigned char Dot_Font_Start = 0;
const unsigned char Dot_Font_Length_Bytes = 8;
const unsigned char Dot_Font_Width = 8;      // full bytes of pixels   8,16,24 etc
const unsigned char Dot_Font_Height = 8;
const unsigned char Dot_Font_Spacing = 1;

const unsigned short Letter_Font[] = {
	0xFE,0x07,0xFE,0x1F,0xFE,0x3F,0x0E,0x3C,0x0E,0x70,0x0E,0x70,0x0E,0x70,0x0E,0x70,0x0E,0x38,0xFE,0x3F,0xFE,0x1F,0xFE,0x0F,0x0E,0x1C,0x0E,0x18,0x0E,0x38,0x0E,0x38,0x0E,0x38,0x0E,0x3C,0xFE,0x1F,0xFE,0x1F,0xFE,0x07, // Code for char num 66 "B"
	0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0xF0,0x01,0xF0,0x0F,0x70,0x0F,0x70,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // Code for char num 114
	0xC0,0x0F,0xF0,0x3F,0xF8,0x3F,0x3C,0x30,0x1C,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00,0xFE,0x3F,0xFE,0x3F,0xFE,0x3F,0x0C,0x38,0x1C,0x3C,0xF8,0x1F,0xF0,0x0F,0xE0,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // Code for char num 101
	0xF0,0x39,0xF8,0x3B,0xFC,0x3F,0x3C,0x3C,0x1C,0x38,0x1C,0x38,0x7C,0x38,0xF8,0x3F,0xF0,0x3F,0xC0,0x3F,0x00,0x38,0x00,0x38,0x00,0x3C,0xF8,0x1F,0xF8,0x1F,0xF0,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // Code for char num 97
	0x80,0x1F,0xC0,0x1F,0xE0,0x1F,0xE0,0x11,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xF8,0x1F,0xF8,0x1F,0xF8,0x1F,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xE0,0x00, // Code for char num 116
	0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x7C,0x3C,0xFC,0x1F,0xDC,0x1F,0x9C,0x0F,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00, // Code for char num 104
	0xC0,0x0F,0xE0,0x0F,0xF0,0x0F,0xF0,0x08,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00, // Code for char num 116
	0x70,0x00,0x70,0x00,0xF0,0x00,0xE0,0x00,0xE0,0x00,0xC0,0x01,0xC0,0x01,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xE0,0x07,0xE0,0x07,0xE0,0x07,0x70,0x0E,0x70,0x0E,0x78,0x1C,0x38,0x1C,0x38,0x1C,0x1C,0x38,0x1C,0x38,0x1C,0x38, // Code for char num 121
	0xFC,0x1F,0xFC,0x1F,0xFC,0x1F,0x38,0x00,0x38,0x00,0x70,0x00,0xE0,0x00,0xC0,0x01,0xC0,0x01,0x80,0x03,0x00,0x07,0x00,0x0E,0x00,0x0E,0xFC,0x1F,0xFC,0x1F,0xFC,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // Code for char num 122
	0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0xFC,0x07,0xFC,0x1F,0xFC,0x3F,0x1C,0x3C,0x1C,0x78,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x78,0x1C,0x3C,0xFC,0x3F,0xFC,0x1F,0xFC,0x07, // Code for char num 80
	0xE0,0x07,0xF0,0x0F,0xF8,0x1F,0x3C,0x3C,0x1C,0x38,0x0E,0x70,0x0E,0x70,0x0E,0x70,0x0E,0x70,0x0E,0x70,0x0E,0x70,0x1C,0x38,0x3C,0x3C,0xF8,0x1F,0xF0,0x0F,0xE0,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // Code for char num 111
	0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xCF,0x30,0xFF,0x3F,0xFB,0x3E,0x73,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // Code for char num 109
	0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0x00,0x00,0x00,0x00,0xC0,0x01,0xC0,0x01,0xC0,0x01, // Code for char num 105
	0x00,0x00,0x00,0x00,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0x00,0x00,0x00,0x00,0x00,0x00 // Code for char num 58
	

	// Code for char num 97
	
};

const unsigned char Letter_Font_Start = 0;
const unsigned char Letter_Font_Length_Bytes = 42;
const unsigned char Letter_Font_Width = 16;      // full bytes of pixels   8,16,24 etc
const unsigned char Letter_Font_Height = 21;
const unsigned char Letter_Font_Spacing = 1;


#endif /* FONTS_H_ */