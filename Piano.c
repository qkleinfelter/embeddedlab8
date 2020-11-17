/*******************************************************************
 * piano.c
 * Instructor: Devinder Kaur
 * Runs on TM4C123
 * There are four keys in the piano
 * Authors: Daniel Valvano,
 * 					Thomas Royko
 * Student: Quinn Kleinfelter
 * Section: 001/003
 * Date:    11/17/2020
 *
 * Port E bits 3-0 have 4 piano keys
 *******************************************************************/

#include "Piano.h"
#include "..//inc//tm4c123gh6pm.h"


// **************Piano_Init*********************
// Initialize piano key inputs
// Input: none
// Output: none
void Piano_Init(void){ 
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x10;					  // Enable Port E Clock
	delay = SYSCTL_RCGC2_R; 				  // delay
	GPIO_PORTE_AMSEL_R &= ~0x0F;		  // disable analog functions
	GPIO_PORTE_PCTL_R &= ~0x0000FFFF; // regular GPIO
	GPIO_PORTE_DIR_R &= ~0x0F;				// PE3-PE0 inputs
	GPIO_PORTE_AFSEL_R &= ~0x0F;			// disable alternate functions
	GPIO_PORTE_PUR_R &= ~0x0F;				// we don't need pullup resistors
	GPIO_PORTE_DEN_R |= 0x0F;					// Digitally enable PE3-PE0
}

// **************Piano_In*********************
// Input from piano key inputs
// Input: none 
// Output: 0 to 15 depending on keys
// 0x01 is key 0 pressed, 0x02 is key 1 pressed,
// 0x04 is key 2 pressed, 0x08 is key 3 pressed
unsigned long Piano_In(void){
  
  return 0; // remove this, replace with input
}
