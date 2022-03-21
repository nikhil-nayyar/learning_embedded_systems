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
#include <stdio.h>

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base){

	uint8_t* curr =  ptr;
	uint8_t size = 0;

  int ascii_zero = 48;
	int ascii_a = 65;

	uint16_t q;
	uint16_t r;

	uint32_t value;	
	if(data >> 31){
		value = -1 * data;
	} else{
	  value = data;
  }


  // Perform conversion
  do{
  
    q =  value / base;
    r =  value % base;
    
		uint8_t digit;

    if(r < 10){
			digit = ascii_zero + r;
		} else{
			digit = ascii_a + (r-10);
		}

		my_memset(curr, 1, digit);
    value = q;
    curr++;
    size++; 
  } while(q != 0);

	//my_reverse(ptr,size);	
	if(data >> 31){
		my_memset(curr,1,45);
		curr=curr+1;
		size++;
	}

	my_reverse(ptr,size);	

	*curr=0;

return size;
} 



int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base){

	
  uint8_t* curr = ptr;
	uint8_t temp;
  uint8_t* temp_digit = &temp; 
  int32_t result=0;

	uint8_t pow = 0;
  for(int i = digits-1; i >= 0; i--){
    
		// Get rightmost (LS) digit
		my_memcopy(curr+i, temp_digit, 1);

		// If the current digit is '-', negate value and return
		if(*(curr+i)==45){ result = result*-1;}
		
		// Add value of digit to total result if integer
		if(*(curr+i) >= 48 && *(curr+1) <= 57){
			result = result +((*temp_digit - 48) * my_pow(base,pow));
		}
		
		// Add value of digit to total result if letter
		if(*(curr+i) >= 65 && *(curr+1) <= 70){
			result = result +((*temp_digit - 65) * my_pow(base,pow));
		}

		pow++;

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
