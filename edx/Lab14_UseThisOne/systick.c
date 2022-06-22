#include "ADC.h"
#include "MeasurementOfDistance.h"
#include "systick.h"
#include "systick_delay.h"
#include "tm4c123gh6pm.h"

void SysTick_Init(void){
	
	// --- reconfigure systick for wait --- //
	NVIC_ST_CTRL_R &=0x00; // disable systick
	NVIC_ST_CTRL_R |= 0x6; 	// enable clock source and interrupt
	
	// set period if not set
	if(NVIC_ST_RELOAD_R == 0){
		// assuming 16MHz -> 62.5ns -> 15999999 counts per second -> 15999 counts per ms
	   NVIC_ST_RELOAD_R = 15999; 
	}
	
  NVIC_ST_CURRENT_R = 0x0; 	// clear current with write
	NVIC_ST_CTRL_R |= 0x1; // 	// enable systick
	
}

void SysTick_Handler(void){
	
	// Decrement Counts
	setAdcCount(getAdcCount()-1);
	setSysTickCount(getSysTickCount()-1);
	
	// Send Data to Main when ADC Flag is active and count is 0
	if(getAdcFlag() && getAdcCount() == 0){
		Distance = ADC0_In();
		Flag = 1;
		setAdcCount(25); // reset count, 25ms between samples in 40 Hz system
	}
	
	if(getSysTickFlag() && getSysTickCount() == 0){
		setSysTickFlag(0);
	}
}
