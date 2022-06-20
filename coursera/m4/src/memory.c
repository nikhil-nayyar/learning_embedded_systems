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
 * @file memory.c
 * @brief Abstraction of memory read and write operations
 *
 * This implementation file provides an abstraction of reading and
 * writing to memory via function calls. There is also a globally
 * allocated buffer array used for manipulation.
 *
 * @author Alex Fosdick
 * @date April 1 2017
 *
 */

#include "memory.h"
#include <stdlib.h>

/***********************************************************
 Function Definitions
***********************************************************/
void set_value(char * ptr, unsigned int index, char value){
  ptr[index] = value;
}

void clear_value(char * ptr, unsigned int index){
  set_value(ptr, index, 0);
}

char get_value(char * ptr, unsigned int index){
  return ptr[index];
}

void set_all(char * ptr, char value, unsigned int size){
  unsigned int i;
  for(i = 0; i < size; i++) {
    set_value(ptr, i, value);
  }
}

void clear_all(char * ptr, unsigned int size){
  set_all(ptr, 0, size);
}

uint8_t* my_memmove(uint8_t* src, uint8_t* dst, size_t length){

	uint8_t* currentS = src;
	uint8_t* T = malloc(length);
	uint8_t* currentT = T;
	uint8_t* currentD = dst;

	for(int i = 0; i < length; i++){
		*currentT = *currentS;
		*currentS = 0;
		currentS++;
		currentT++;
	}

	currentT = T;

  for(int i = 0; i < length; i++){
		*currentD = *currentT;
    currentT++;
		currentD++;
	}

	free(T);

	return dst;

}

uint8_t* my_memcopy(uint8_t* src, uint8_t* dst, size_t length){

	uint8_t* currentS = src;
	uint8_t* currentD = dst;

  for(int i = 0; i < length; i++){
		*currentD = *currentS;
    currentS++;
		currentD++;
	}

	return dst;

}

uint8_t* my_memset(uint8_t* src, size_t length, uint8_t value){

	uint8_t* current = src;

	for(int i = 0; i < length; i++){
		*current = value;
		current++;
	}

	return src;

}


uint8_t* my_memzero(uint8_t* src, size_t length){

	uint8_t* result = my_memset(src,length,0);
	
	return result;

}


uint8_t* my_reverse(uint8_t* src, size_t length){
/*
	size_t length_half = length / 2;

	uint8_t* stack;
	
	if(length % 2){
		stack = malloc(length_half+1);
	} else{
		stack = malloc(length_half);
	}

	uint8_t* front = src; 
  uint8_t* back = src + length-1;

	// Operate on first half of data
	for(int i = 0; i < length_half; i++){
	
		//Place value at front ptr on stack
		*stack = *front;

		// Place value at back ptr on front ptr
		*front = *back;

		// Increment front ptr
		front++;

		// Decrement back ptr
		back--;

		// Increment Stack ptr
		stack++;

	}

	// Decrement stack pointer to most recently add value
	stack--;

	// Operate on second half of data
	for(int i = 0; i < length_half; i++){

		//Place value from stack on front pointer
		*front = *stack;

		// Decrement stack
		stack--;

		// Increment front
		front++;		
	}
	*/

	uint8_t* temp = malloc(length);

	for(int i = 0; i < length; i++){
		*(temp+(length-1-i)) = *(src+i);
	}
	for(int i = 0; i < length; i++){
		*(src+i) = *(temp+i);
	}

	return src;

}

uint32_t* reserve_words(size_t length){

	uint32_t* result = malloc(length*4);

	return result;

}

void free_words(uint32_t* src){

	free(src);

}

