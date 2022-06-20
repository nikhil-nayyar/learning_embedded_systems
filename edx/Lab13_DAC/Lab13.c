// Lab13.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// edX Lab 13 
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// Port B bits 3-0 have the 4-bit DAC
// Port E bits 3-0 have 4 piano keys

#include "..//tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include <Math.h>
#include "TExaS.h"

// global variables
unsigned long input;
unsigned short playing;
unsigned long period;
unsigned long periods[4] = {2388, 2128, 1896, 1595};

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void delay(unsigned long msec);
int main(void){ // Real Lab13 
	// for the real board grader to work 
	// you must connect PD3 to your DAC output
  TExaS_Init(SW_PIN_PE3210, DAC_PIN_PB3210,ScopeOn); // activate grader and set system clock to 80 MHz
// PortE used for piano keys, PortB used for DAC        
  Sound_Init(); // initialize SysTick timer and DAC
  Piano_Init();
  EnableInterrupts();  // enable after all initialization are done
	playing = 0;
	input = 0x0;
  while(1){                
  // input from keys to select tone
		
		// Get button input
		input = Piano_In();
		
		delay(10);
		
		// If input is zero and playing, shut off
		if (!input && playing){
			input = 0;
			Sound_Off();
			playing = 0;
		} 
		
		else if(input != Piano_In()){
			
			int i;
			
			// Store most recent input
			input = Piano_In();

			// Generate Period
			// Select period associated with highest key

			for(i = 3; i >= 0; i--){
				if( input >> i){
					period = periods[i];
					break;
				}
			}
			
			// Start SysTick Interrupt
			Sound_Tone(period);
			
			playing = 1;

		} 
		


  }
            
}

// Inputs: Number of msec to delay
// Outputs: None
void delay(unsigned long msec){ 
  unsigned long count;
  while(msec > 0 ) {  // repeat while there are still delay
    count = 16000;    // about 1ms
    while (count > 0) { 
      count--;
    } // This whoop takes approximately 3 cycles
    msec--;
  }
}


