## Author
Nikhil Nayyar
## Course 
Introduction to Embedded Systems Software and Development Environment

##Purpose
This repository contains the code for UC Boulder's introductory embedded systems course. The repo is divided into the various module assignments that allow me to implement the material I am learning from the course.

## Breakdown
### Module 1
The first module serves as a (re)introduction to C. The goal was to implement some basic C statistical functions in the stats.h and stats.c files.
### Module 2
The second module serves as a crash course in building files. The goal was to implement a Makefile that enabled cross platform compiliation via a flag set in the command line call to make. Thus, it involved extensive use of Make variables and conditionals in addition to the implementation of calls to gcc with the proper flags. All development by me was completed in the files sources.mk and Makefile.
### Module 3
The third module revolved around the analysis of Memory usage in a given C file. No code was explicitly written for this module but various utilities and analysis files were used. The analysis was conducted primarily with the following: 
- nm binary utility
- readelf
- gcc generation of .map files
### Final
The final project puts all the information together. The crux of the programming is to implement some memory management functions. This involves allocating/freeing words and then using specific data types (uint8-t) to perform data manipulation. Ultimately, this was to implement both an itoa and atoi conversion function. The project brought together all of the information learned in this introduction such as compilation and using make as a build manager.
