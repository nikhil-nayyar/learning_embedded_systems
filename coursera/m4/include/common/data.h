/**
 * @file data.h
 * @brief Abstraction of string-to-ASCII and ASCII-to-string conversions
 *
 * This header file provides an abstraction of converting between
 * ASCII and string
 *
 * @author Nikhil Nayyar
 * @date 17 March 2022
 *
 */
#ifndef __DATA_H__
#define __DATA_H__

#include <stdint.h>

/**
 * @brief Convert a given integer to ASCII string
 *
 * Given an input integer and integer base, convert the number 
 * to an ASCII string
 *
 * @param data integer value to convert to string
 * @param ptr Index pointing to new string
 * @param base number base of input integer
 *
 * @return void.
 */
uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base);

/**
 * @brief Convert a given string to ASCII integers
 *
 * Given a pointer to an an ASCII string and a base, return 
 * a 32 bit integer representation of the number
 *
 * @param ptr Pointer to ASCII string
 * @param digits Number of digits in character set
 * @param base for the new integer
 *
 * @return void.
 */
int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base);

/**
 * @brief implments INTEGER power operation
 * 
 * Given a base and power, returns the result of base^power
 *
 * @param base base of power function
 * @param power power of power function
*/

int32_t my_pow(int32_t base, int32_t power);

#endif /* __DATA.h__ */	
