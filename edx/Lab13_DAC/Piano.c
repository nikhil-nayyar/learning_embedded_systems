// Piano.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// There are four keys in the piano
// Daniel Valvano
// December 29, 2014

// Port E bits 3-0 have 4 piano keys

#include "Piano.h"
#include "..//tm4c123gh6pm.h"


// **************Piano_Init*********************
// Initialize piano key inputs
// Input: none
// Output: none
void Piano_Init(void){ 
	
	unsigned long delay;
	
	// Enable Port E
	SYSCTL_RCGCGPIO_R |= 0x10;
	delay = SYSCTL_RCGCGPIO_R;
	
	// Enable Digital, Disable Analog
	GPIO_PORTE_DEN_R |= 0xF;
	GPIO_PORTE_AMSEL_R |= 0x0;
	
	// Set Direction
	GPIO_PORTE_DIR_R = 0x0;

	// Disable Alternate Function
  GPIO_PORTE_AFSEL_R = 0x0;
}
// **************Piano_In*********************
// Input from piano key inputs
// Input: none 
// Output: 0 to 15 depending on keys
// 0x01 is key 0 pressed, 0x02 is key 1 pressed,
// 0x04 is key 2 pressed, 0x08 is key 3 pressed
unsigned long Piano_In(void){
	
	unsigned long input = GPIO_PORTE_DATA_R;

  return input; // remove this, replace with input
}
