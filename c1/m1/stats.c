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
 * @file stats.c 
 * @brief functions for gathering various stats for a given array
 *
 * Contains various functions for analyzing a given array such as sorting the array or finding the max,min, median, or mean value.
 *
 * @author Nikhil Nayyar
 * @date 2/21/2022
 *
 */

#include <stdio.h>
#include "stats.h"

/* Size of the Data Set */
#define SIZE (40)

void main() {

  unsigned char test[SIZE] = { 34, 201, 190, 154,   8, 194,   2,   6,
                              114, 88,   45,  76, 123,  87,  25,  23,
                              200, 122, 150, 90,   92,  87, 177, 244,
                              201,   6,  12,  60,   8,   2,   5,  67,
                                7,  87, 250, 230,  99,   3, 100,  90};

  /* Other Variable Declarations Go Here */
  /* Statistics and Printing Functions Go Here */

  printf("Joe Biden");

}

/* Add other Implementation File Code Here */

void print_statistics(char* arr){
}

void print_array(char* arr, int len){
}

int find_median(char* arr, int len){
    return 0;
}

int find_mean(char* arr, int len){
    return 0;
}

int find_maximum(char* arr, int len){
    return 0;
}

int find_minimum(char* arr, int len){
    return 0;
}

void sort_array(char* arr, int lne){
}


