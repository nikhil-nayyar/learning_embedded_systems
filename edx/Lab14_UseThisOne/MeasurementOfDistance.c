// MeasurementOfDistance.c
// Runs on LM4F120/TM4C123
// Use SysTick interrupts to periodically initiate a software-
// triggered ADC conversion, convert the sample to a fixed-
// point decimal distance, and store the result in a mailbox.
// The foreground thread takes the result from the mailbox,
// converts the result to a string, and prints it to the
// Nokia5110 LCD.  The display is optional.
// January 15, 2016

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2015

 Copyright 2016 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// Slide pot pin 3 connected to +3.3V
// Slide pot pin 2 connected to PE2(Ain1) and PD3
// Slide pot pin 1 connected to ground


#include "ADC.h"
#include "..//tm4c123gh6pm.h"
#include "MeasurementOfDistance.h"
#include "lcd.h"
#include "systick.h"
#include "systick_delay.h"

void EnableInterrupts(void);  // Enable interrupts

unsigned static char String[10]; // null-terminated ASCII string
unsigned static long ADCdata;    // 12-bit 0 to 4095 sample
unsigned long Distance;
unsigned long Flag;       // 1 means valid Distance, 0 means Distance is empty
unsigned long TimerFlag;    // 1 means SysTick Triggered

//********Convert****************
// Convert a 12-bit binary ADC sample into a 32-bit unsigned
// fixed-point rotation (resolution 0.066deg).  Calibration
// data is gathered using known distances and reading the
// ADC value measured on PE1.  
// Overflow and dropout should be considered 
// Input: sample  12-bit ADC sample
// Output: 32-bit degree rotation (resolution 0.066deg)
unsigned long Convert(unsigned long sample){
  return sample*.066;  
}


//-----------------------UART_ConvertRotation-----------------------
// Converts a 32-bit distance into an ASCII string
// Input: 32-bit number to be converted (resolution 0.001cm)
// Output: store the conversion in global variable String[10]
// Fixed format 1 digit, point, 3 digits, space, units, null termination
// Examples
//    4 to "0.004 cm"  
//   31 to "0.031 cm" 
//  102 to "0.102 cm" 
// 2210 to "2.210 cm"
//10000 to "*.*** cm"  any value larger than 9999 converted to "*.*** cm"
void UART_ConvertRotation(unsigned long n){
// as part of Lab 11 you implemented this function
	
	// Loop Controls
	unsigned short nonZero = 0;
	unsigned short i;
	
	// Division Variables
	unsigned long divisor = n;
	unsigned long dividend = 100;
	unsigned long quotient;
	unsigned long remainder;
	
	for(i=0; i < 10; i++){
		
		// Add Decimal Place
		if(i==3 && n==0){
			String[i] = ' ';
			continue;
		} else if(i==3 && n!=0){
			String[i] = '.';
			continue;		
		}
		
		// Terminate and add deg unit
		if (i == 7){
			String[7] = 'd';
			String[8] = 'e';
			String[9] = 'g';
			break;
		}

		// Perform conversion from number to ASCII
		quotient = divisor / dividend;
		remainder = divisor % dividend;
		
		if(quotient == 0 && !nonZero){
			String[i] = ' ';
		} else if (quotient == 0){
			String[i] = '0';
		} else{
			String[i] = quotient + 48;
			nonZero = 1;
		}
		
		divisor = remainder;
		dividend /= 10;
			

	}
	
}



// once the ADC and convert to distance functions are operational,
// you should use this main to build the final solution with interrupts and mailbox
 int main(void){ 
  volatile unsigned long delay;
	SysTick_Init(); // initialize SysTick for 16000Hz interrupts
	LCD_16x2_Init_Simple();
  ADC0_Init();   // initialize ADC0, channel 1, sequencer 3
	
	LCD_16x2_Clear();
	LCD_16x2_Test_HelloWorld();
	delayNms(3000); 
	 
	LCD_16x2_Clear();
	LCD_16x2_Test_Morbius();
	delayNms(3000);
	 
	LCD_16x2_Clear();
	
  while(1){ 
	// read mailbox if data present
	if(Flag){
		float rotation = Convert(Distance);
		UART_ConvertRotation(rotation); // generate data in string form
		LCD_16x2_Write_Row_1(String); 
		Flag = 0; // Clear Flag
	}
	
  }
}
