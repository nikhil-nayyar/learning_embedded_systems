// ***** 0. Documentation Section *****
// TableTrafficLight.c for Lab 10
// Runs on LM4F120/TM4C123
// Index implementation of a Moore finite state machine to operate a traffic light.  
// Daniel Valvano, Jonathan Valvano
// January 15, 2016

// east/west red light connected to PB5
// east/west yellow light connected to PB4
// east/west green light connected to PB3
// north/south facing red light connected to PB2
// north/south facing yellow light connected to PB1
// north/south facing green light connected to PB0
// pedestrian detector connected to PE2 (1=pedestrian present)
// north/south car detector connected to PE1 (1=car present)
// east/west car detector connected to PE0 (1=car present)
// "walk" light connected to PF3 (built-in green LED)
// "don't walk" light connected to PF1 (built-in red LED)

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"

#define LED_RED_SOUTH 			(*((volatile unsigned long *)0x40005010)) //PB2
#define LED_YELLOW_SOUTH		(*((volatile unsigned long *)0x40005008)) //PB1
#define LED_GREEN_SOUTH			(*((volatile unsigned long *)0x40005004)) //PB0
#define LED_RED_WEST				(*((volatile unsigned long *)0x40005080)) //PB5
#define LED_YELLOW_WEST			(*((volatile unsigned long *)0x40005040)) //PB4
#define LED_GREEN_WEST			(*((volatile unsigned long *)0x40005020)) //PB3
#define LED_RED_WALK				(*((volatile unsigned long *)0x40025008)) //PF1
#define LED_GREEN_WALK			(*((volatile unsigned long *)0x40025020)) //PF3
#define SENSOR_SOUTH				(*((volatile unsigned long *)0x40024008)) //PE1
#define SENSOR_WEST					(*((volatile unsigned long *)0x40024004)) //PE0
#define SENSOR_WALK					(*((volatile unsigned long *)0x40024010)) //PE2
	
#define SYSCTRL_RCC					(*((volatile unsigned long *)0x400FE060))
#define SYSCTRL_RCC2				(*((volatile unsigned long *)0x400FE070))
#define SYSTICK_CONTROL 		(*((volatile unsigned long *)0xE000E010))
#define SYSTICK_CURRENT			(*((volatile unsigned long *)0xE000E018))
#define SYSTICK_RELOAD			(*((volatile unsigned long *)0xE000E014))
	
#define WAIT_1S 						Systick_Wait10ms(100);
#define WAIT_100S						Systick_Wait10ms(10);

// ***** 2. Global Declarations Section *****

// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Board_Init(void); // Initialize Board Registers
void Systick_Init(void); // Initialize Systick
void LED_Diagnostic(void); // output test
void Switch_Diagnostic(void); // input test
void Systick_Wait(unsigned long delay); // Wait subroutine
void Systick_Wait10ms(unsigned long delay); // Wait routine
unsigned int getInput(void); // Return value 0-8 depending on switch inputs
void setOutput(void);

// STATE PROTOTYPES: Each state defined
struct State;
typedef struct State StateType;

struct State {
	char state[8];
  unsigned long Out;       // Output
  unsigned long Time;     // Time in 10ms increments
  unsigned long Next[8]; // Transitions
};

/*
const StateType SOUTHG1 = {0411,1000,{1,2,2,2,1,2,2,2}        };
const StateType SOUTHG2 = {0411,1000,{0,2,2,2,0,2,2,2}        };
const StateType SOUTHY0 = {0211,1000,{0,6,3,3,0,6,3,3}        };
const StateType WESTG1 =  {0141,1000,{4,5,4,5,5,5,5,5}        };
const StateType WESTG2 =  {0141,1000,{3,5,3,5,5,5,5,5}        };
const StateType WESTY0 =  {0121,1000,{3,6,3,6,0,6,0,6}        };
const StateType WALKG1 =  {0114,1000,{7,7,8,8,8,8,8,8}        };
const StateType WALKG2 =  {0114,1000,{6,6,8,8,8,8,8,8}        };
const StateType WALKB0 =  {0111,500, {9,9,9,9,9,9,9,9}        };
const StateType WALKB1 =  {0114,500, {10,10,10,10,10,10,10,10}};
const StateType WALKB2 =  {0111,500, {11,11,11,11,11,11,11,11}};
const StateType WALKB3 =  {0114,500, {12,12,12,12,12,12,12,12}};
const StateType WALKB4 =  {0111,500, {13,13,13,13,13,13,13,13}};
const StateType WALKB5 =  {0114,500, {7,7,3,3,0,0,0,0}        };

const StateType states[]={SOUTHG1,SOUTHG2,SOUTHY0,WESTG1,WESTG2,WESTY0,WALKG1,WALKG2,WALKB0,WALKB1,WALKB2,WALKB3,WALKB4,WALKB5};
*/

const StateType states[]={
	{"SOUTHG1",0411,100,{1,2,2,2,1,2,2,2}        },
	{"SOUTHG2",0411,100,{0,2,2,2,0,2,2,2}        },
	{"SOUTHY0",0211,100,{0,6,3,3,0,6,3,3}        },
	{"WESTG1", 0141,100,{4,5,4,5,5,5,5,5}        },
	{"WESTG2", 0141,100,{3,5,3,5,5,5,5,5}        },
	{"WESTY0", 0121,100,{3,6,3,6,0,6,0,6}        },
	{"WALKG1", 0114,100,{7,7,8,8,8,8,8,8}        },
	{"WALKG2", 0114,100,{6,6,8,8,8,8,8,8}        },
	{"WALKB0", 0111,50, {9,9,9,9,9,9,9,9}        },
	{"WALKB1", 0110,50, {10,10,10,10,10,10,10,10}},
	{"WALKB2", 0111,50, {11,11,11,11,11,11,11,11}},
	{"WALKB3", 0110,50, {12,12,12,12,12,12,12,12}},
	{"WALKB4", 0111,50, {13,13,13,13,13,13,13,13}},
	{"WALKB5", 0110,50, {7,7,3,3,0,0,0,0}        }
};

StateType curr;
unsigned int input;

// ***** 3. Subroutines Section *****
int main(void){ 
  TExaS_Init(SW_PIN_PE210, LED_PIN_PB543210,ScopeOff); // activate grader and set system clock to 80 MHz
	Board_Init();              // Initialize Board
	Systick_Init();           // Initialize Systick
	LED_Diagnostic();        // Test LEDs
	Switch_Diagnostic();    // Test Switches
  EnableInterrupts();    // Enable interrupts
	Systick_Wait10ms(20); // Wait 200ms;
	
	
	curr = states[0];
	
  while(1){
		
		input = getInput();
		curr = states[curr.Next[input]]; // Get next state
		setOutput(); // Set LEDs for new state
		Systick_Wait10ms(curr.Time); // Delay before next state change
		
  }
}


void Board_Init(void){
	volatile unsigned long delay;
	
	// 1) Enable Port B, E, F clocks
  SYSCTL_RCGC2_R |= 0x00000032;      
	
	// delay to allow clock to stabilize
  delay = SYSCTL_RCGC2_R;                
	
	// 2) disable analog function
  GPIO_PORTB_AMSEL_R &= 0x00;      
	GPIO_PORTE_AMSEL_R &= 0x00;    
	GPIO_PORTF_AMSEL_R &= 0x00;    
  
	// 3) GPIO clear bit PCTL
  GPIO_PORTB_PCTL_R &= 0x00000000; 
  GPIO_PORTE_PCTL_R &= 0x00000000;  
  GPIO_PORTF_PCTL_R &= 0x00000000;  	

	// 4.1) PE0, PE1, PE2 input
  GPIO_PORTE_DIR_R = 0x00; 

  // 4.2) PF1, PF3, PB0, PB1, PB2, PB3, PB4, PB5 output
  GPIO_PORTB_DIR_R = 0x3F;          
	GPIO_PORTF_DIR_R = 0x0A;
	
	// 5) no alternate function
	GPIO_PORTB_AFSEL_R &= 0x00;
  GPIO_PORTE_AFSEL_R &= 0x00;
  GPIO_PORTF_AFSEL_R &= 0x00;

  // 6) enable digital pins
  GPIO_PORTB_DEN_R = 0x3F;    
	GPIO_PORTE_DEN_R = 0x07;          
	GPIO_PORTF_DEN_R = 0x0A;          
}

void Systick_Init(void){
	
	// Bypass PLL
	SYSCTRL_RCC |= (0x1 << 11);
	
	// Clear USESYS
	SYSCTRL_RCC &= ~(0x1 << 22);
	
	// Set XTAL
	SYSCTRL_RCC &= ~(0x1F << 6);
	SYSCTRL_RCC |= (0x15 << 6);
	
	// Set OSCSRC (leave as default)
	
	// Clear PWRDN
	SYSCTRL_RCC &= ~(0x1 << 13);

	// Clean Bypass
	SYSCTRL_RCC &= ~(0x1 << 11);

	// Configure STCTRL and unbypass
	SYSTICK_CONTROL = 0x05;
}

void Systick_Wait(unsigned long delay){
  SYSTICK_RELOAD = delay-1;  // number of counts to wait
  SYSTICK_CURRENT = 0x0000;       // any value written to CURRENT clears
  while((SYSTICK_CONTROL&0x00010000)==0){ // wait for count flag
  }
}

void Systick_Wait10ms(unsigned long delay){
	// 80000 cycles in 10ms (per 80MHz system clock speed);
	//unsigned long cycles = 160000;
	unsigned long cycles = 800000;
	
	// Multiply cycles by total increments of 10ms (delay) desired
	int i;
	for(i = 0; i < delay; i++){
		Systick_Wait(cycles);	
	}
	
}

void LED_Diagnostic(void){
	
		LED_GREEN_SOUTH = 0xFF;
	  WAIT_100S 
		LED_YELLOW_SOUTH = 0xFF;
		WAIT_100S 
		LED_RED_SOUTH = 0xFF;
	  WAIT_100S 
		LED_GREEN_WEST = 0xFF;
	  WAIT_100S 
		LED_YELLOW_WEST = 0xFF;
	  WAIT_100S 
		LED_RED_WEST = 0xFF;
	  WAIT_100S 
		LED_GREEN_WALK = 0xFF;
	  WAIT_100S 
		LED_RED_WALK = 0xFF;
	  WAIT_100S 
		
		LED_GREEN_SOUTH = 0x00;
		WAIT_100S 
		LED_YELLOW_SOUTH = 0x00;
		WAIT_100S 
		LED_RED_SOUTH = 0x00;
		WAIT_100S 
		LED_GREEN_WEST = 0x00;
		WAIT_100S 
		LED_YELLOW_WEST = 0x00;
		WAIT_100S 
		LED_RED_WEST = 0x00;
		WAIT_100S 
		LED_GREEN_WALK = 0x00;
		WAIT_100S 
		LED_RED_WALK = 0x00;
		WAIT_100S 
}

void Switch_Diagnostic(void){

	LED_GREEN_SOUTH = 0xFF;
	LED_YELLOW_SOUTH = 0xFF;
	LED_RED_SOUTH = 0xFF;
	while(!SENSOR_SOUTH){
	}
	LED_GREEN_SOUTH = 0x00;
	LED_YELLOW_SOUTH = 0x00;
	LED_RED_SOUTH = 0x00;
	
	LED_GREEN_WEST = 0xFF;
	LED_YELLOW_WEST = 0xFF;
	LED_RED_WEST = 0xFF;
	while(!SENSOR_WEST){
	}
	LED_GREEN_WEST = 0x00;
	LED_YELLOW_WEST = 0x00;
	LED_RED_WEST = 0x00;
	
	LED_GREEN_WALK = 0xFF;
	while(!SENSOR_WALK){
	}
	LED_GREEN_WALK = 0x00;

}

unsigned int getInput(void){

	unsigned short south = SENSOR_SOUTH << 1;
	unsigned short west =  SENSOR_WEST << 1;
	unsigned short walk =  SENSOR_WALK >> 2;
		
	return south+west+walk;

}

void setOutput(void){

	unsigned long out = curr.Out;

	LED_RED_SOUTH 		= ((out >>	6) & 01 ? 0xFF : 0x00);
	LED_YELLOW_SOUTH	= ((out >>	7) & 01 ? 0xFF : 0x00);
	LED_GREEN_SOUTH		= ((out >>	8) & 01 ? 0xFF : 0x00);
	LED_RED_WEST			= ((out >>	3) & 01 ? 0xFF : 0x00);
	LED_YELLOW_WEST 	= ((out >>	4) & 01 ? 0xFF : 0x00);
	LED_GREEN_WEST 		= ((out >>	5) & 01 ? 0xFF : 0x00);
	LED_RED_WALK	 		= ((out >>	0) & 01 ? 0xFF : 0x00);
	LED_GREEN_WALK 		= ((out >>	2) & 01 ? 0xFF : 0x00);

}

