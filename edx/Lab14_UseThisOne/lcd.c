#include "lcd.h"
#include <string.h>
#include "systick_delay.h"
#include "tm4c123gh6pm.h"

// --- Initialization and Reset --- //
void LCD_16x2_Init_Simple(void){

	LCD_16x2_Init();
	LCD_16x2_Control_Config(ON,NO_CURSOR,NO_BLINKING);
	LCD_16x2_Entry_Config(INCREMENT,NO_SCROLL);
	LCD_16x2_Function_Config(BIT8,LINE2,DOT40);
	
}

void LCD_16x2_Init(void){
	
	// declare local variables
	volatile unsigned long delay;
	
	unsigned long activeA = 0x3C;
	unsigned long activeF = 0x07;
	unsigned long activeD = 0x0F;
	
	// --- initialize clock for ports A, D, F --- // 
	SYSCTL_RCGC2_R = 0x29;
	delay = SYSCTL_RCGCGPIO_R;
	
	// --- configure port A --- // 
	GPIO_PORTA_DIR_R = activeA;
	GPIO_PORTA_DEN_R = activeA;	
	GPIO_PORTA_AMSEL_R =0x0;
	GPIO_PORTA_AFSEL_R &= 0x0;

	// --- configure port D --- // 
	GPIO_PORTD_DIR_R = activeD;
	GPIO_PORTD_DEN_R = activeD;	
	GPIO_PORTD_AMSEL_R = 0x0;
	GPIO_PORTD_AFSEL_R &= 0x0;
	
	// --- configure port F --- // 
	GPIO_PORTF_LOCK_R  = 0x4C4F434B;
	GPIO_PORTF_CR_R = 0x1;
	GPIO_PORTF_DIR_R = activeF;
	GPIO_PORTF_DEN_R = activeF;	
	GPIO_PORTF_AMSEL_R = 0x0;
	GPIO_PORTF_AFSEL_R &= 0x0;
	
	LCD_16x2_Clear();
}

void LCD_16x2_Clear(void){
	
	unsigned char data = 0x01;
	unsigned char control = 0x4;
	
	LCD_16x2_Transmit_Command(data, control);
}

void LCD_16x2_Return(void){

	unsigned char data = 0x2;
	unsigned char control = 0x0;
	
	LCD_16x2_Transmit_Command(data,control);
}

void LCD_16x2_Control_Config(unsigned char on, unsigned char cursor, unsigned char blinking){
	
	unsigned char data = 0x08;
	data |= (on << 2);
	data |= (cursor << 1);
	data |= (blinking << 0);
	
	
	unsigned char control = 0x0;
	
	LCD_16x2_Transmit_Command(data, control);
}

void LCD_16x2_Function_Config(unsigned char length,  unsigned char lines, unsigned char font){
	
	unsigned char data = 0x20;
	data |= (length << 4);
	data |= (lines << 3);
	data |= (font << 2);
	
	unsigned char control = 0x0;
	
	LCD_16x2_Transmit_Command(data, control);
	
}

void LCD_16x2_Entry_Config(unsigned char increment, unsigned char scroll){
	unsigned char data = 0x4;
	data |= (increment << 1);
	data |= (scroll << 0);
	unsigned char control = 0x0;
	
	LCD_16x2_Transmit_Command(data,control);
}

// --- RAM and Cursor Manipulation --- //
void LCD_16x2_Cursor_Shift(unsigned char direction){

	unsigned char control = 0x0;
	unsigned char data = 0x10;
	data |= (direction << 2);
	
	LCD_16x2_Transmit_Command(data,control);
	
}

void LCD_16x2_Set_DDRAM(unsigned char addr){
	
	unsigned char control = 0x0;
	unsigned char data = 0x80;
	data |= addr;
	
	LCD_16x2_Transmit_Command(data,control);

}

void LCD_16x2_Shift_Display(unsigned char direction){
	unsigned char control = 0x0;
	unsigned char data = 0x18;
	data |= (direction << 2);
	
	LCD_16x2_Transmit_Command(data,control);
	
}

// --- Data/Command Writing (Instruction) --- //
void LCD_16x2_Write_Character(unsigned char data){
	unsigned char control = 0x1;
	LCD_16x2_Transmit_Command(data,control);
}

void LCD_16x2_Write_Row_1(char string[]){

	// Set DDRAM to 0x00;
	LCD_16x2_Set_DDRAM(0x00);
	
	// Write string
	for(unsigned int i = 0; i < strlen(string); i++){
		LCD_16x2_Write_Character(string[i]);
	}
	
}

void LCD_16x2_Write_Row_2(char string[]){

	// Set DDRAM to 0x40;
	LCD_16x2_Set_DDRAM(0x40);
	
	// Write string
	for(unsigned int i = 0; i < strlen(string); i++){
		LCD_16x2_Write_Character(string[i]);
	}
	
}


// --- Data/Command Writing (Physical) --- //
void LCD_16x2_Transmit_Command(unsigned char data, unsigned char ctrl){
	
	unsigned char hi = (data & 0xF0) >> 4;
	unsigned char lo = (data & 0x0F);
	
	LCD_16x2_Enable_OFF();
  LCD_16x2_Transmit_Command_HI(hi);
	LCD_16x2_Transmit_Command_LO(lo);
	LCD_16x2_Transmit_Command_CTRL(ctrl);
  LCD_16x2_Enable_ON();
	delayNms(10);
	LCD_16x2_Enable_OFF();
}

void LCD_16x2_Transmit_Command_HI(unsigned char data){
	data = data << 2;
	GPIO_PORTA_DATA_R = 0x0;
	GPIO_PORTA_DATA_R |= data;
}


void LCD_16x2_Transmit_Command_LO(unsigned char data){
	GPIO_PORTD_DATA_R = 0;
	GPIO_PORTD_DATA_R |= data;
}


void LCD_16x2_Transmit_Command_CTRL(unsigned char data){
	GPIO_PORTF_DATA_R = 0;
	GPIO_PORTF_DATA_R |= data;
}

void LCD_16x2_Enable_ON(){
	GPIO_PORTF_DATA_R |= 0x4;
}

void LCD_16x2_Enable_OFF(){
	GPIO_PORTF_DATA_R &= ~( (unsigned long) 0x4);
}


// --- Testing & Diagnostic Functions --- //
void LCD_16x2_Test_ABCD(void){
	LCD_16x2_Write_Character('a');
	LCD_16x2_Write_Character('b');
	LCD_16x2_Write_Character('c');
	LCD_16x2_Write_Character('d');	
}

void LCD_16x2_Test_HelloWorld(void){
	
	LCD_16x2_Write_Row_1("Hello World");
	
}

void LCD_16x2_Test_Morbius(void){
	
	LCD_16x2_Write_Row_1("It's Morbing");
	LCD_16x2_Write_Row_2("Time");
	
}
