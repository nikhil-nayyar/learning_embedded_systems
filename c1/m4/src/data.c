/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file main.c
 * @brief Main entry point to the C1M4 Assessment
 *
 * This file contains the main code for the C1M4 assesment. Students
 * are not to change any of the code, they are instead supposed to compile
 * these files with their makefile.
 *
 * @author Alex Fosdick
 * @date April 1 2017
 *
 */

#include "data.h"
#include "memory.h"
#include <math.h>

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base){

  int max_power;
  int q;
  int r;

  // Get highest power of number
  int i = 1;
  do{

    q = data / my_pow(base,i);
    max_power = i;
    i++;

  } while(q != 0);

  // Set up values for conversion
  max_power--;
  int value = data;
  int ascii_zero = 48;
  uint8_t* curr = ptr;
  

  // Perform conversion
  do{
  
    q = value / my_pow(base,max_power);
    r =  value % my_pow(base,max_power);
    
    my_memset(curr, 1, ascii_zero + q);
    value = r;
    max_power--;
    curr++;
    
  } while(max_power > -1);
  
  return max_power;
} 



int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base){

  uint8_t* curr = ptr;

	uint8_t temp;
  uint8_t* temp_digit = &temp; 
  int32_t result;

  int ascii_zero = 48;
  for(int i = digits-1; i > 0; i--){
    my_memcopy(curr, temp_digit, 1);
    result = result + ((*temp_digit - ascii_zero) * my_pow(base,i));
    curr++;
  }

  return result;

}

int32_t my_pow(int32_t base, int32_t power){
	
	int32_t result = 1;

	for(int i = 0; i < power; i++){
		result = result * base;
	}

	return result;
}
