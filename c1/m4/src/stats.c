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
#include <stdlib.h>
#include <unistd.h>
#include "stats.h"

int cmpfunc(const void *a, const void *b);

/* Size of the Data Set */
#define SIZE (40)

void main() {

  unsigned char test[SIZE] = { 34, 201, 190, 154,   8, 194,   2,   6,
                              114, 88,   45,  76, 123,  87,  25,  23,
                              200, 122, 150, 90,   92,  87, 177, 244,
                              201,   6,  12,  60,   8,   2,   5,  67,
                                7,  87, 250, 230,  99,   3, 100,  90};

  print_array(test, SIZE);

  // Must sort array to ensure functions work properly
  sort_array(test, SIZE);

  print_statistics(test);

}

/* Add other Implementation File Code Here */

void print_statistics(char* arr){

   printf("Mean   : %hhu\n", find_mean(arr,SIZE));
   printf("Median : %hhu\n", find_median(arr,SIZE));
   printf("Minimum: %hhu\n", find_minimum(arr,SIZE));
   printf("Maximum: %hhu\n", find_maximum(arr,SIZE));

}

void print_array(char* arr, int len){
   for(int i = 0; i < len; i++){
      printf("%hhu ",arr[i]);
   } printf("\n");
}

int find_median(char* arr, int len){

     // Calculates index at middle of array
     int m = len / 2;

     // returns value at median index
     return arr[m];
}

int find_mean(char* arr, int len){
    
    int m = 0;
    
    // iterates through values and gets cum sum
    for(int i = 0; i < len; i++){
         m = m + arr[i];
    }
 
    // divides cum sum by total num to get avg
    m = m / len;

    return m;
}

int find_maximum(char* arr, int len){
    // returns value at greatest end of array
    return arr[0];
}

int find_minimum(char* arr, int len){
    // retruns value at smallest end of array
    return arr[len-1];
}

void sort_array(char* arr, int len){
   // makes call to std library quicksort function
   qsort(arr,len,1,cmpfunc);
}


// Function used in qsort algorithm
int cmpfunc(const void *a, const void *b){
	unsigned char arg1 = *(const char*)a;
	unsigned char arg2 = *(const char*)b;

	// Configured s.t. array is greatest - smallest
	if(arg1 > arg2){
	  return -1;
	}

	if(arg1 < arg2){
	  return 1;
	}

	return 0;
}

