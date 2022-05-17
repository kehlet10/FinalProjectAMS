/*-------------------------------------------------------------------
  File name: "lcd162.c"

  Driver for "LCD Keypad Shield" alphanumeric display.
  Display controller = HD44780U (LCD-II).
  
  Max. uC clock frequency = 16 MHz (Tclk = 62,5 ns)

  Connection : PORTx (4 bit mode) :
  [LCD]        [Portx]
  RS   ------  PH 5
  RW   ------  GND
  E    ------  PH 6
  DB4  ------  PG 5
  DB5  ------  PE 3
  DB6  ------  PH 3
  DB7  ------  PH 4

  Henning Hargaard, February 5, 2018
---------------------------------------------------------------------*/
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
// Enabling us to use macro _NOP() to insert the NOP instruction
#include <avr/cpufunc.h>
#include "lcd162.h"

// library function itoa() is needed
#include <stdlib.h>
#include <string.h>

// Defines
#define adcRes 1023
#define supply 5

//*********************** PRIVATE (static) operations *********************
static void waitBusy(unsigned char instruction)
{
  // "Clear display" and "Return Home" executes 1,52 ms
  if (instruction < 0b00000100)
  _delay_ms(2);
  // - all other instructions executes 37 us
  else
  _delay_us(50);
}  

static void pulse_E()
{
  PORTH |= 0b01000000; // Set bit 6/E HIGH
  _NOP();			   // Wait 4 clock cycles
  _NOP();
  _NOP();
  _NOP();
  PORTH &= 0b10111111; // Set bit 6/E LOW
  _NOP();			   // Wait 4 clock cycles
  _NOP();
  _NOP();
  _NOP();
}

// Sets the display data pins according to the 4 lower bits of data
static void set4DataPins(unsigned char data)
{
  PORTH = (PORTH & 0b11100111) | ((data<<1) & 0b00011000);
  PORTE = (PORTE & 0b11110111) | ((data<<2) & 0b00001000);
  PORTG = (PORTG & 0b11011111) | ((data<<5) & 0b00100000);  
}

static void sendInstruction(unsigned char data)
{      	
  PORTH &= 0b11011111;	
  _NOP();
  set4DataPins(data>>4);
  pulse_E();
  PORTH |= 0b00100000;
  
  
  PORTH &= 0b11011111;
  _NOP();
  set4DataPins(data);
  pulse_E();
  PORTH |= 0b00100000;
  
  _delay_ms(2);
}

static void sendData(unsigned char data)
{      
  PORTH |= 0b00100000;
  _NOP();
  set4DataPins(data>>4);
  pulse_E();
  PORTH &= 0b00000000;
  _NOP();
  PORTH |= 0b00100000;
  _NOP();
  set4DataPins(data);
  pulse_E();
  PORTH &= 0b00000000;
  
  _delay_ms(2);
}

//*********************** PUBLIC functions *****************************

// Initializes the display, blanks it and sets "current display position"
// at the upper line, leftmost character (cursor invisible)
// Reference: Page 46 in the HD44780 data sheet
void LCDInit()
{
  // Initialize PWM for backlight
  DDRB |= 0b00010000;
  TCCR2A = 0b11000011;
  TCCR2B = 0b00000011;
  OCR2A = 0;
  
  // Initialize ADC for keys
  ADCSRA = 0b10000111; // Enable and set prescaler to 128
  ADMUX |= 0b01000000;
  ADMUX &= 0b11000000;
  ADCSRB &= 0b11110111;
	
  // Initializing the used port
  DDRH |= 0b01111000;  // Outputs
  DDRE |= 0b00001000;
  DDRG |= 0b00100000;
  
  // Wait 50 ms (min. 15 ms demanded according to the data sheet)
  _delay_ms(50);
  // Function set (still 8 bit interface)
  PORTG |= 0b00100000;
  PORTE |= 0b00001000;
  pulse_E();
  
  // Wait 10 ms (min. 4,1 ms demanded according to the data sheet)
  _delay_ms(10);
  // Function set (still 8 bit interface)
  pulse_E();

  // Wait 10 ms (min. 100 us demanded according to the data sheet)
  _delay_ms(10);
  // Function set (still 8 bit interface)
  pulse_E();

  // Wait 10 ms (min. 100 us demanded according to the data sheet)
  _delay_ms(10);
  // Function set (now selecting 4 bit interface !)
  PORTG &= 0b11011111;
  pulse_E();

  // Function Set : 4 bit interface, 2 line display, 5x8 dots
  sendInstruction( 0b00101000 );
  // Display, cursor and blinking OFF
  sendInstruction( 0b00001000 );
  // Clear display and set DDRAM adr = 0	
  sendInstruction( 0b00000001 );
  // By display writes : Increment cursor / no shift
  sendInstruction( 0b00000110 );
  // Display ON, cursor and blinking OFF
  sendInstruction( 0b00001100 );
  
  Timer2_Init();
  ADC_Init();
}

// Blanks the display and sets "current display position" to
// the upper line, leftmost character
void LCDClear()
{
  sendInstruction(0b00000001);
}

// Sets DDRAM address to character position x and line number y
void LCDGotoXY( unsigned char x, unsigned char y )
{
  unsigned char a;
  
  if(y == 0){
	  
	  a = 0b10000000 | x;
	  sendInstruction(a);
  } 
  else{
	  a = 0b11000000 | x;
	  sendInstruction(a);  
  }
}

// Display "ch" at "current display position"
void LCDDispChar(char ch)
{
  sendData(ch);
}

// Displays the string "str" starting at "current display position"
void LCDDispString(char* str)
{
	for(size_t i; i < strlen(str); i++){
		LCDDispChar(str[i]);
	}  
}

// Displays the value of integer "i" at "current display position"
void LCDDispInteger(int i)
{
	
  char* toDisplay = 0;
  itoa(i, toDisplay, 10);
  
  LCDDispString(toDisplay);
}

// Loads one of the 8 user definable characters (UDC) with a dot-pattern,
// pre-defined in an 8 byte array in FLASH memory
void LCDLoadUDC(unsigned char UDCNo, const unsigned char *UDCTab)
{
  // To be implemented		
}

// Selects, if the cursor has to be visible, and if the character at
// the cursor position has to blink.
// "cursor" not 0 => visible cursor.
// "blink" not 0 => the character at the cursor position blinks.
void LCDOnOffControl(unsigned char cursor, unsigned char blink)
{
  char onOff = 0b00001100;
  
  if(cursor == 1)
  {
	  onOff |= 0b00000010; 
  }
	
  if(blink == 1)
  {
	  onOff |= 0b00000001;
  }
	
  sendInstruction(onOff);
}

// Moves the cursor to the left
void LCDCursorLeft()
{
  sendInstruction(0b00010000);
}

// Moves the cursor to the right
void LCDCursorRight()
{
  sendInstruction(0b00010100);
}

// Moves the display text one position to the left
void LCDShiftLeft()
{
  sendInstruction(0b00011000);
}

// Moves the display text one position to the right
void LCDShiftRight()
{
  sendInstruction(0b00011100);
}

// Sets the backlight intensity to "percent" (0-100)
void setBacklight(unsigned char percent)
{
	if(percent <= 100){
		OCR2A = (percent/100)*255;
	}
}

// Reads the status for the 5 on board keys
// Returns 0, if no key pressed
unsigned char readKeys()
{	
	if(ADCW < 50)
	{
		return 1;
	} 
	else if (ADCW < 195)
	{
		return 2;
	}
	else if (ADCW < 380)
	{
		return 3;
	}
	else if (ADCW < 555)
	{
		return 4;
	}
	else if (ADCW < 790)
	{
		return 5;
	}	
		
	return 0;
	
  /*ADCSRA |= 0b01000000;
  
  while(ADCSRA &= 0b0100000){}
	  
  unsigned int adcVal = ADCW;
  unsigned int adcResult = (adcVal*supply)/adcRes;*/
  
}

void Timer2_Init() 
{
	// Fast PWM, OC2A ( = PB4) Non-Inverted mode
	TCCR2A = 0b10000011;
	// Prescaler = 1024
	TCCR2B = 0b00000111;
	// 25% Duty Cycle
	OCR2A = 255/4;
	// Pin OC1A ( = PB4 ) is output
	DDRB |= (1<<4);
}

void ADC_Init()
{
	// ADC Reference = 5V | Input = ADC0
	ADMUX = 0b01000000;
	// ADC Enabled | Free Running | No interrupts | Prescaler = 128
	ADCSRA = 0b11100111;
	ADCSRB = 0b00000000;
}