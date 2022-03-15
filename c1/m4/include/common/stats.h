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
 * @file stats.h 
 * @brief definitions for various statistical functions
 *
 * Provides definitions for various statistical functions to be performed on an inputted array of characters.
 *
 * @author Nikhil Nayyar
 * @date 2/21/2022
 *
 */

#ifndef __STATS_H__
#define __STATS_H__

/**
 * @brief prints relevant stats for inputted array
 *
 * makes relevant function calls to find_minimum(), find_maximum(), find_mean(), and find_median() and prints formatted output to stream
 *
 * @param arr character array for which to calculate stats
 */
void print_statistics(char* arr);

/**
 * @brief prints character array
 *
 * prints characters to output stream for a given array
 *
 * @param arr character array for which to print each element
 * @param len number of elements in arr
 */
void print_array(char* arr, int len);

/**
 * @brief return median character for a given array
 *
 * Given an array of character, return the chracter that is in the middle of the sorted array of characters
 *
 * @param arr character array for which to find median
 * @param len number of elements in arr
 *
 * @return median character that appears in middle of sorted array
 */
int find_median(char* arr, int len);

/**
 * @brief return character that represents average of all values in array
 *
 * @param arr character array for which to find mean
 * @param len number of elements in arr
 *
 * @return mean character that represents average of all values in array
 */
int find_mean(char* arr, int len);

/**
 * @brief returns maximum value in an array
 *
 * given an array of characters, return the character that represents the maximum ASCII/Unicode value
 *
 * @param arr character array for which to find max value
 * @param len number of elements in arr
 *
 * @return max character that is the maximum value
 */
int find_maximum(char* arr, int len);


/**
 * @brief returns minimum value in an array
 *
 * given an array of characters, return the character that represents the minimum ASCII/Unicode value
 *
 * @param arr character array for which to find min value
 * @param len number of elements in arr
 *
 * @return min character that is the minimum value
 */int find_minimum(char* arr, int len);

/**
 * @brief sort the inputted character array from largest to smallest
 *
 * sorts the character array such that the 0th element is the largest in value and the n-1th element is the smallest value
 *
 * @param arr character array for which to find min value
 * @param len number of elements in arr
 *
 */
void sort_array(char* arr, int len);

#endif /* __STATS_H__ */
