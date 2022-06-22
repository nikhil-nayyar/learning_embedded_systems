#include "systick_delay.h"
#include "systick.h"
#include "tm4c123gh6pm.h"

int SysTickCount;
int SysTickFlag;


void delayNms(int ms){
	
	// Set Flag to 1 for SysTick Handler
	SysTickCount = ms;	
	setSysTickFlag(1);
	
	while(getSysTickFlag()){
	}
		
}

unsigned int getSysTickCount(void){
	return SysTickCount;
}

void setSysTickCount(int count){
	SysTickCount = count;
}

void setSysTickFlag(int flag){
	SysTickFlag = flag;
}

unsigned char getSysTickFlag(){
	return SysTickFlag;
}
