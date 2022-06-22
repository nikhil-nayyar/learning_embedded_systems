#ifndef MEASUREMENT_OF_DISTANCE
#define MEASUREMENT_OF_DISTANCE

unsigned extern long Distance;
unsigned extern long Flag; 

unsigned long Convert(unsigned long sample);
void UART_ConvertRotation(unsigned long n);

#endif