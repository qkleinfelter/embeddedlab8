/*******************************************************************
 * Lab8.c
 * Instructor: Devinder Kaur
 * Runs on TM4C123
 * Use SysTick interrupts to implement a 4-key digital piano
 * Authors: Daniel Valvano,
 *					Jonathan Valvano,
 * 					Thomas Royko
 * Student: Quinn Kleinfelter
 * Section: 001/003
 * Date:    11/17/2020
 *
 * Port B bits 3-0 have the 4-bit DAC
 * Port E bits 3-0 have 4 piano keys
 *******************************************************************/

#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void delay(unsigned long msec);
void InitPortF(void);


int main(void){ // Real Lab13 
	// for the real board grader to work 
	// you must connect PD3 to your DAC output
	// activate grader and set system clock to 80 MHz
  TExaS_Init(SW_PIN_PE3210, DAC_PIN_PB3210,ScopeOn);
	
	// PortE used for piano keys, PortB used for DAC
	InitPortF();
  Sound_Init(); // initialize SysTick timer and DAC
  Piano_Init();
  EnableInterrupts();  // enable after all initialization are done
  
	while(1){                
		// input from keys to select tone

  }
            
}

void InitPortF(void) {
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000020;				// Enable Port F clock
	delay = SYSCTL_RCGC2_R;							// delay
	GPIO_PORTF_LOCK_R = 0x4c4F434B;			// Unlock Port F
	GPIO_PORTF_CR_R = 0x04;							// Allow changes on PF2
	GPIO_PORTF_AMSEL_R = 0x00;					// Disable analog function
	GPIO_PORTF_PCTL_R = 0x00000000;			// Regular GPIO
	GPIO_PORTF_DIR_R = 0x04;						// PF2 output
	GPIO_PORTF_AFSEL_R = 0x00;					// disable alternate function
	GPIO_PORTF_PUR_R = 0x00;						// no pullup resistors
	GPIO_PORTF_DEN_R = 0x04;						// digitally enable PF2
}

void delay(unsigned long msec){ 
  unsigned long count;
  while(msec > 0 ) {  // repeat while there are still delay
    count = 16000;    // about 1ms
    while (count > 0) { 
      count--;
    } // This while loop takes approximately 3 cycles
    msec--;
  }
}
