// ***** 0. Documentation Section *****
// SwitchLEDInterface.c for Lab 8
// Runs on LM4F120/TM4C123
// Use simple programming structures in C to toggle an LED
// while a button is pressed and turn the LED on when the
// button is released.  This lab requires external hardware
// to be wired to the LaunchPad using the prototyping board.
// January 15, 2016
//      Jon Valvano and Ramesh Yerraballi

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"

#define GPIO_PORTE_LED      		(*((volatile unsigned long *)0x40024008))
#define GPIO_PORTE_SWITCH      	(*((volatile unsigned long *)0x40024004))

// ***** 2. Global Declarations Section *****

short button;

// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Board_Init(void); // Contains code for initializing board
void Delay1ms(unsigned long msec);

// ***** 3. Subroutines Section *****

// PE0, PB0, or PA2 connected to positive logic momentary switch using 10k ohm pull down resistor
// PE1, PB1, or PA3 connected to positive logic LED through 470 ohm current limiting resistor
// To avoid damaging your hardware, ensure that your circuits match the schematic
// shown in Lab8_artist.sch (PCB Artist schematic file) or 
// Lab8_artist.pdf (compatible with many various readers like Adobe Acrobat).
int main(void){ 
//**********************************************************************
// The following version tests input on PE0 and output on PE1
//**********************************************************************
  TExaS_Init(SW_PIN_PE0, LED_PIN_PE1, ScopeOn);  // activate grader and set system clock to 80 MHz
	Board_Init();																	// Initialize Ports
  EnableInterrupts();           // enable interrupts for the grader
	
	// Initialize LED as on
	GPIO_PORTE_LED = 0xFF;
	
  while(1){                     // main loop
		
    button = GPIO_PORTE_SWITCH;

		// Flash LED while button held down
		while(button){
			button = GPIO_PORTE_SWITCH;
			GPIO_PORTE_LED = ~GPIO_PORTE_LED;
			Delay1ms(100);
		}
		
		// Reset LED to high
	 	GPIO_PORTE_LED = 0xFF;
		
  }
  
}

void Board_Init(void){
	SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOE; // Set up clock #define SYSCTL_RCGC2_GPIOE      
	// 0x00000010  // Port E Clock Gating Control
	GPIO_PORTE_LOCK_R = 0x4C4F434B; // Unlock port E
	GPIO_PORTE_CR_R = 0x0003; // Allow change to PE0 and PE1
	GPIO_PORTE_DIR_R = 0x0002; // Set PE0 to input, PE1 to output
	GPIO_PORTE_AFSEL_R = 0x0000; 	// Set no alternate function
	GPIO_PORTE_PCTL_R = 0x0000; 	// Set no alternate function
	GPIO_PORTE_DEN_R = 0x0003; 	 // Set PE0 and PE1 to digital
	GPIO_PORTE_AMSEL_R = 0x0000; // Set PE0 and PE1 to not analog
	GPIO_PORTE_DATA_R = 0x0000; // Initialize data to 0;
	GPIO_PORTE_PUR_R = 0x0000; 	 // Don't Set Pull up Resistor for PE0 and PE1
}

void Delay1ms(unsigned long msec){
	// When the assembly of the loop completes 16000 times, 1 msec passes
	// Assembly loop is 5 cycles
	// Clock is 80MHz
	// i = 16000loops/ms = 80e3/5
	// msec scalar multiplied
	int i = 16000 * msec;
	while(i > 0){
		i = i - 1;
	}
}
