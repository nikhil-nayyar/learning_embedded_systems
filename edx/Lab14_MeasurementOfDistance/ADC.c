// ADC.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0 SS3 to be triggered by
// software and trigger a conversion, wait for it to finish,
// and return the result. 
// Daniel Valvano
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

#include "ADC.h"
#include "..//tm4c123gh6pm.h"

// This initialization function sets up the ADC 
// Max sample rate: <=125,000 samples/second
// SS3 triggering event: software trigger
// SS3 1st sample source:  channel 1
// SS3 interrupts: enabled but not promoted to controller
void ADC0_Init(void){ 
	
	volatile unsigned short delay;
	
	// ------ Configure GPIO Pin for ADC0 ------ // 
	SYSCTL_RCGC2_R  |= 0x00000010;    // Set Port E Clock to Run
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTE_LOCK_R=0x4C4F434B; // Enable Writing to CR Register
  GPIO_PORTE_CR_R  |= 0x4;      // Enable Commits for Bit 2 on Port E
	GPIO_PORTE_DIR_R &= ~(0x4);   // Set E2 to Input
	GPIO_PORTE_DEN_R &= ~(0x4);   // Disable Digital
	GPIO_PORTE_AMSEL_R |= (0x4);  // Enable Analog
	GPIO_PORTE_AFSEL_R |= (0x4);  // Enable Alternate Function 
	
	// ------ Configure ADC0 ------ // 
	SYSCTL_RCGC0_R |= SYSCTL_RCGC0_ADC0; // Enable ADC0 Clock
	SYSCTL_RCGC0_R |= SYSCTL_RCGC0_ADC1SPD_125K; // Set Lowest Maximum Sample Rate 
	delay = SYSCTL_RCGC0_R;
	ADC0_ACTSS_R &= ~(0x0008); // Disable Sequencer
	ADC0_SSPRI_R = 0x0123;  // Set sequencer 3 as the highest priority
  ADC0_EMUX_R	 &= ~(0xF000); // Enable Software Trigger
  ADC0_SSMUX3_R |= 0x1; // MUX3 for sequencer 3, Value 1 for AIN1 on PE2	
	ADC0_SSCTL3_R |= 0x6; // MUX3 for sequencer 3, Interrupt Enable Bit set, bit Enable for sample sequence
	ADC0_ACTSS_R |= 0x8; // Enable Sequencer
}


//------------ADC0_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
unsigned long ADC0_In(void){  
	
	unsigned long result;
	ADC0_PSSI_R |= 0x8; // Initiate Sample Sequence
	while( (ADC0_RIS_R & 0x8) == 0 ){} // Wait until Sequence Complete
	result = ADC0_SSFIFO3_R; // Read ADC value from FIFO
	ADC0_ISC_R = (0x8);	// Acknowledge Result by clearing interrupt bit [bit cleared by writing a one to it]
			
  return result; // replace this line with proper code
}
