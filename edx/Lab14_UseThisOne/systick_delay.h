#ifndef SYSTICK_DELAY
#define SYSTICK_DELAY

/*
 * delay for N ms
 */ 
void delayNms(int ms);

void delay1ms(void);

unsigned int getSysTickCount(void);

void setSysTickCount(int count);

unsigned char getSysTickFlag();

void setSysTickFlag(int f);

#endif
