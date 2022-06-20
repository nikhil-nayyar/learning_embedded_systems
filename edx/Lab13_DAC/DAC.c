// DAC.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Implementation of the 4-bit digital to analog converter
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// Port B bits 3-0 have the 4-bit DAC

#include "DAC.h"
#include "..//tm4c123gh6pm.h"

#define DAC_OUT (*(volatile unsigned long *)0x4000503C)

// **************DAC_Init*********************
// Initialize 6-bit DAC 
// Input: none
// Output: none
void DAC_Init(void){
	
	unsigned long delay;
	
	// Enable Port B
	SYSCTL_RCGCGPIO_R |= 0x02;
	delay = SYSCTL_RCGCGPIO_R;
	
	// Set pins as output
	GPIO_PORTB_DIR_R |= 0x1F;
	
	// Enable Digital / Disable Analog
	GPIO_PORTB_DEN_R = 0x1F;
	GPIO_PORTB_AMSEL_R = 0x00;
	
	// Disable Alternate Function
	GPIO_PORTB_AFSEL_R = 0x00;
}


// **************DAC_Out*********************
// output to DAC
// Input: 6-bit data, 0 to 64 
// Output: none
void DAC_Out(unsigned long data){
	GPIO_PORTB_DATA_R = data << 2;
}
