// Sound.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Use the SysTick timer to request interrupts at a particular period.
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// This routine calls the 4-bit DAC

#include "Sound.h"
#include "DAC.h"
#include "..//tm4c123gh6pm.h"
#define STCTRL     (*((volatile unsigned long *) 0xE000E010))
#define STRELOAD   (*((volatile unsigned long *) 0xE000E014))
#define STCURRENT  (*((volatile unsigned long *) 0xE000E018))
	
// Global Variables
unsigned int output;
unsigned short i;           // Index varies from 0 to 15
const unsigned short SineWave[16] = {36, 45, 54, 63, 63, 63, 54, 45, 36, 27, 18, 9, 9, 9, 18, 27};
																		
// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Also calls DAC_Init() to initialize DAC
// Input: none
// Output: none
void Sound_Init(void){
	
	// Initialize DAC
	DAC_Init();
  
	// Initialize SysTick Interrupts
	// Disable Systick
	STCTRL &= ~(0x1);
	
	// Set clock source
	STCTRL |= 0x4;
	
	// Enable Interrupts
	STCTRL |= 0x2;
	
}

// **************Sound_Tone*********************
// Change Systick periodic interrupts to start sound output
// Input: interrupt period
//           Units of period are 12.5ns
//           Maximum is 2^24-1
//           Minimum is determined by length of ISR
// Output: none
void Sound_Tone(unsigned long period){
// this routine sets the RELOAD and starts SysTick
	
	// Load RELOAD register with designated period value;
	STRELOAD = period - 1;
		
	// Write to Current to Clear
	// STCURRENT = 0;
	
	// Set Level Value
	i = 0;
	
	// Enable SysTick 
	STCTRL |= 0x1;

}


// **************Sound_Off*********************
// stop outputing to DAC
// Output: none
void Sound_Off(void){
 // this routine stops the sound output
	
	// Disable Systick
	STCTRL &= ~(0x1);
	
	// Output zero
	DAC_Out(0);
}


// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void){
   
	i = (i+1) & (0xF);
	output = SineWave[i];
	DAC_Out(output);
	
}
