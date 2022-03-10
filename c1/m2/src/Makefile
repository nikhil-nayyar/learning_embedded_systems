#******************************************************************************
# Copyright (C) 2017 by Alex Fosdick - University of Colorado
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are 
# permitted to modify this and use it to learn about the field of embedded
# software. Alex Fosdick and the University of Colorado are not liable for any
# misuse of this material. 
#
#*****************************************************************************

#------------------------------------------------------------------------------
# Makefile that allows for two target platforms
# 	MSP432 MCU 
# 	Host System
#
# Use: make [TARGET] [PLATFORM-OVERRIDES]
#
# Build Targets:
#      <FILE>.o - Builds <FILE>.o object file
#      build - Builds and links all source file
#      all - Same as build
#      clean - removes all generated files
#
# Platform Overrides:
#      PLATFORM - target system (HOST, MSP432)
#
#------------------------------------------------------------------------------

# include relevant source file
include sources.mk

# Platform Override
PLATFORM = HOST 

# Architectures Specific Flags
LINKER_FILE = ../msp432p401r.lds 
CPU = cortex-m0plus 
ARCH = thumb
SPECS = nosys.specs

# Compiler Flags and Defines

## General Flags
TARGET = c1m2

## Host Specific Flags
ifeq ($(PLATFORM), HOST)
CC = gcc
LD = ld 
LDFLAGS = -Wl -Map=$(TARGET).map  
CFLAGS = -Wall $(INCLUDES_HOST) 
CPPFLAGS = -D $(PLATFORM) 
endif

## MSP432 Specific Flags
ifeq ($(PLATFORM),MSP432)
CC = arm-none-eabi-gcc
LD = ld
LDFLAGS = -Wl -Map=$(TARGET).map -T$(LINKER_FILE) 
CFLAGS = -Wall $(INCLUDES_MSP432) -mcpu=$(CPU) -m$(ARCH) --specs$(SPECS) 
CPPFLAGS = -D $(PLATFORM)
endif


# 
ifeq ($(PLATFORM), HOST)
main.o: main.c 
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

memory.o: memory.c 
	$(CC)  $(CPPFLAGS) $(CFLAGS) -c $< -o $@

startup_msp432p401r.o: startup_msp432p401r.c  
	$(CC)  $(CPPFLAGS) $(CFLAGS) -c $< -o $@

system_msp432p401r.o: system_msp432p401r.c 
	$(CC)  $(CPPFLAGS) $(CFLAGS)  -c $< -o $@

interrupts_msp432p401r.o: interrupts_msp432p401r.c 
	$(CC)  $(CPPFLAGS) $(CFLAGS) -c $< -o $@

endif

#
ifeq ($(PLATFORM), MSP432)
main.o: main.c 
	$(CC)  $(CPPFLAGS) $(CFLAGS) -c $< -o $@

memory.o: memory.c 
	$(CC)  $(CPPFLAGS) $(CFLAGS) -c $< -o $@

startup_msp432p401r.o: startup_msp432p401r.c  
	$(CC)  $(CPPFLAGS) $(CFLAGS) -c $< -o $@

system_msp432p401r.o: system_msp432p401r.c 
	$(CC)  $(CPPFLAGS) $(CFLAGS)  -c $< -o $@

interrupts_msp432p401r.o: interrupts_msp432p401r.c 
	$(CC)  $(CPPFLAGS) $(CFLAGS) -c $< -o $@

endif

