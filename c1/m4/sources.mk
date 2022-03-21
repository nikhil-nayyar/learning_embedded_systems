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

# Add your Source files to this variable
SOURCES_MSP432 = course1.c \
		data.c \
		stats.c \
	  	main.c \
	 	memory.c \
	  	startup_msp432p401r.c \
	  	system_msp432p401r.c \
	  	interrupts_msp432p401r.c

SOURCES_HOST = course1.c\
	       data.c\
	       main.c\
	       memory.c\
				stats.c

# Add your include paths to this variable
INCLUDES_MSP432 = -I include/common \
	   -I include/CMSIS \
	   -I include/msp432 \

INCLUDES_HOST = -I include/common \
