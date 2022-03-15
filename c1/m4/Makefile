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

#------------------------------------------------------------------------------

# Compiler Flags and Defines

## General Flags
TARGET = c1m2
GENERAL = -Wall -Werror -g -O0 -std=c99

# Architectures Specific Flags (for use with MSP432)
LINKER_FILE = ../msp432p401r.lds 
CPU = cortex-m4
FPU=fpv4-sp-d16
FLOAT=hard
ARCH = armv7e-m
SPECS = nosys.specs
ARCHFLAGS = -mcpu=$(CPU) -mfpu=$(FPU) -mfloat-abi=$(FLOAT) \
	   -march=$(ARCH) -mthumb --specs=$(SPECS)

ifeq ($(PLATFORM), HOST)
SOURCES = SOURCES_HOST
else
SOURCES = SOURCES_MSP432
endif

## Host Specific Flags
ifeq ($(PLATFORM), HOST)
CC=gcc
else
CC=arm-none-eabi-gcc
endif

ifeq ($(PLATFORM), HOST)
LD=ld
else
LD=ld
endif

ifeq ($(PLATFORM), HOST)
LDFLAGS= -Wl,-Map=../bin/$(TARGET).map -Wl,-o,../bin/$(TARGET).out,-lc 
else
LDFLAGS= -Wl,-Map,../bin/$(TARGET).map -Wl,-T,$(LINKER_FILE) -Wl,-o,../bin/$(TARGET).out
endif


ifeq ($(PLATFORM), HOST)
CFLAGS= $(GENERAL) $(INCLUDES_HOST) 
else
CFLAGS= $(GENERAL) $(INCLUDES_MSP432) $(ARCHFLAGS)
endif


ifeq ($(PLATFORM), HOST)
CPPFLAGS= -DHOST
else
CPPFLAGS= -DMSP432 
endif

#------------------------------------------------------------------------------

# Make Build Rules

OBJS = $(SOURCES_HOST:.c=.o)
OBJSPATH = $(addprefix ../bin/, $(OBJS))

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -M $< > ../bin/$<.dep
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -c $< -o ../bin/$@

%.i: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -E $< -o ../pp/$@

%.asm: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -S $< -o ../asm/$@
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -c $< -o ../bin/$@
	objdump -D ../bin/$(@:.o=.asm) > ../asm/$@.obj

.PHONY: build
build: all

.PHONY: all
all: compile-all
	$(CC) $(OBJSPATH) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o ../bin/$(TARGET).out 

.PHONY: compile-all
compile-all: $(OBJS)

.PHONY: clean
clean:
	rm -f ../asm/*
	rm -f ../bin/*
	rm -f ../pp/*
