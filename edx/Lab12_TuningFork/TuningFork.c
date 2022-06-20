// TuningFork.c Lab 12
// Runs on LM4F120/TM4C123
// Use SysTick interrupts to create a squarewave at 440Hz.  
// There is a positive logic switch connected to PA3, PB3, or PE3.
// There is an output on PA2, PB2, or PE2. The output is 
//   connected to headphones through a 1k resistor.
// The volume-limiting resistor can be any value from 680 to 2000 ohms
// The tone is initially off, when the switch goes from
// not touched to touched, the tone toggles on/off.
//                   |---------|               |---------|     
// Switch   ---------|         |---------------|         |------
//
//                    |-| |-| |-| |-| |-| |-| |-|
// Tone     ----------| |-| |-| |-| |-| |-| |-| |---------------
//
// Daniel Valvano, Jonathan Valvano
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


#include "TExaS.h"
#include "..//tm4c123gh6pm.h"
#include <stdio.h>

#define INPUT  (*((volatile unsigned long *)0x40004020)) //PA3
#define OUTPUT (*((volatile unsigned long *)0x40004010)) //PA2
#define STCTRL (*((volatile unsigned long *)0xE000E010))
#define STRELOAD (*((volatile unsigned long *)0xE000E014))
#define STCURRENT (*((volatile unsigned long *)0xE000E018))

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode

// global values
int input;
short output;

// Initialize Port A3 as Positive Logic Switch
void Board_Init(void){

	volatile unsigned long delay;
	
	// Enable Port A
	SYSCTL_RCGC2_R |= 0x1;
	delay = SYSCTL_RCGC2_R;                

	// Set Direction Register
	GPIO_PORTA_DIR_R = GPIO_PORTA_DIR_R | 0x4;
	
	// Set Alternative Function
	GPIO_PORTA_AFSEL_R = 0x00;
	GPIO_PORTA_PCTL_R &= 0x00000000; 
	
	// Set pull up/down as needed
	GPIO_PORTA_PDR_R = GPIO_PORTA_PDR_R | 0xC;
	
	// Set Digital Enable
	GPIO_PORTA_DEN_R = GPIO_PORTA_DEN_R | 0xC;  
	
	// Set Analog Disable
	GPIO_PORTA_AMSEL_R  = 0x00;
}
	
void SysTick_Init(void){

	// Clear Enable
	STCTRL &= ~(0x1);
	
	// Set Reload Register
	STRELOAD |= 90908;
	
	// write to current to clear counter
	STCURRENT = 0x0;
	
	// chose desired mode (specify clock)
	STCTRL |= (0x4);
	
	// Set Interrupt Mode (off initially)
	STCTRL |= (0x0);
	
	// Set Enable
	STCTRL |= 0x1;
	
}

// input from PA3, output from PA2, SysTick interrupts
void Sound_Init(void){ 
	Board_Init();
	SysTick_Init();
}

// called at 880 Hz
void SysTick_Handler(void){
	output = ~output;
	OUTPUT = output;
}

int main(void){// activate grader and set system clock to 80 MHz
  TExaS_Init(SW_PIN_PA3, HEADPHONE_PIN_PA2,ScopeOn); 
  Sound_Init();         
  EnableInterrupts();   // enable after all initialization are done
	
	output = 0x0000;
	
  while(1){
    // main program is free to perform other tasks
		input = INPUT;
		if(input){
			STCTRL |= (0x2);
		} else{
			STCTRL &= ~(0x2);
			OUTPUT = 0x0000;
		}
		
    // do not use WaitForInterrupt() here, it may cause the TExaS to crash
  }
}
