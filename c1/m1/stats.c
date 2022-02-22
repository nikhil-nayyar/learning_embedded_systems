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
#include <unistd.h>
#include "stats.h"

/* Size of the Data Set */
#define SIZE (5)

void qs(char* arr, int lo, int hi);

void swap(char* arr, int a, int b);

int partition(char* arr, int lo, int hi);


void main() {

  unsigned char test[5] = {5,2,1,4,3};

  print_array(test, SIZE);

  sort_array(test, SIZE);

  print_array(test,SIZE);

}

/* Add other Implementation File Code Here */

void print_statistics(char* arr){
}

void print_array(char* arr, int len){
   for(int i = 0; i < len; i++){
      printf("%hhu ",arr[i]);
   } printf("\n");
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

void sort_array(char* arr, int len){
    qs(arr, 0,SIZE);
}

void qs(char* arr, int lo, int hi){

   if(lo >= hi){return;}

   int p = partition(arr,lo,hi);
   print_array(arr,SIZE);
   sleep(3);
   qs(arr,lo,p);
   qs(arr,p+1,hi);

}

int partition(char* arr, int lo, int hi){

   int p = hi;
   int l = lo-1;
   int r = hi+1;

   while(1){
   do{
      l++;
   }
   while(arr[l] < arr[p]);

   do{
      r--;
   }
   while(arr[r] > arr[p]);

   if(l>=r){
      return r;
   }
   swap(arr,l,r);
   }

}

void swap(char* arr, int a, int b){
	int t = arr[a];
	arr[a] = arr[b];
	arr[b] = t;
}
