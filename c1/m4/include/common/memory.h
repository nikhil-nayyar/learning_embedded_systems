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
 * @file memory.h
 * @brief Abstraction of memory read and write operations
 *
 * This header file provides an abstraction of reading and
 * writing to memory via function calls. 
 *
 * @author Alex Fosdick
 * @date April 1 2017
 *
 */
#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Sets a value of a data array 
 *
 * Given a pointer to a char data set, this will set a provided
 * index into that data set to the value provided.
 *
 * @param ptr Pointer to data array
 * @param index Index into pointer array to set value
 * @param value value to write the the locaiton
 *
 * @return void.
 */
void set_value(char * ptr, unsigned int index, char value);

/**
 * @brief Clear a value of a data array 
 *
 * Given a pointer to a char data set, this will clear a provided
 * index into that data set to the value zero.
 *
 * @param ptr Pointer to data array
 * @param index Index into pointer array to set value
 *
 * @return void.
 */
void clear_value(char * ptr, unsigned int index);

/**
 * @brief Returns a value of a data array 
 *
 * Given a pointer to a char data set, this will read the provided
 * index into that data set and return the value.
 *
 * @param ptr Pointer to data array
 * @param index Index into pointer array to set value
 *
 * @return Value to be read.
 */
char get_value(char * ptr, unsigned int index);

/**
 * @brief Sets data array elements to a value
 *
 * Given a pointer to a char data set, this will set a number of elements
 * from a provided data array to the given value. The length is determined
 * by the provided size parameter.
 *
 * @param ptr Pointer to data array
 * @param value value to write the the locaiton
 * @param size Number of elements to set to value
 *
 * @return void.
 */
void set_all(char * ptr, char value, unsigned int size);

/**
 * @brief Clears elements in a data array
 *
 * Given a pointer to a char data set, this will set a clear a number
 * of elements given the size provided. Clear means to set to zero. 
 *
 * @param ptr Pointer to data array
 * @param size Number of elements to set to zero
 *
 * @return void.
 */
void clear_all(char * ptr, unsigned int size);

/**
 * @brief moves length of bytes from source to destination
 *
 * Given a pointer to a source and a length, move the length of bytes from source 
 * to the destination
 *
 * @param src pointer to source
 * @param dst pointer to destination
 * @param length number of bytes to transfer from source to destination
 *
 * @return void.
 */
uint8_t* my_memmove(uint8_t* src, uint8_t* dst, size_t length);

/**
 * @brief copies length of bytes from source to destination
 *
 * Given a pointer to a source and a length, copy the length of bytes from source 
 * to the destination
 *
 * @param src pointer to source
 * @param dst pointer to destination
 * @param length number of bytes to transfer from source to destination
 *
 * @return void.
 */
uint8_t* my_memcopy(uint8_t* src, uint8_t* dst, size_t length);

/**
 * @brief Set all length bytes at source destination to value
 *
 * Given a pointer to a source, replace length number of bytes 
 * with the given value
 *
 * @param src pointer to src
 * @param length number of bytes to set
 * @param value value to set all bytes to
 *
 * @return void.
 */
uint8_t* my_memset(uint8_t* src, size_t length, uint8_t value);

/**
 * @brief Set all length bytes at source destination to 0
 *
 * Given a pointer to a source, replace length number of bytes 
 * with zero
 *
 * @param src pointer to src
 * @param length number of bytes to set
 *
 * @return void.
 */
uint8_t* my_memzero(uint8_t* src, size_t length);

/**
 * @brief Set all length bytes at source destination to 0
 *
 * Given a pointer to a source, reverse the length bytes
 *
 * @param src pointer to src
 * @param length number of bytes to reverse
 *
 * @return void.
 */
uint8_t* my_reverse(uint8_t* src, size_t length);

/**
 * @brief allocate the length number of words starting at source
 *
 * Given a number of words, allocate said words in dynamic memory 
 *
 * @param length Number of words to reserve
 *
 * @return void.
 */
uint32_t* reserve_words(size_t length);

/**
 * @brief free a dynamic allocation by providing source
 *
 * Given a pointer source, free dynamic memory allocation
 *
 * @param src Pointer to data array
 *
 * @return void.
 */
void free_words(uint32_t* src);

#endif /* __MEMORY_H__ */
