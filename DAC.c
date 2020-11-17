/*******************************************************************
 * DAC.c
 * Instructor: Devinder Kaur
 * Runs on TM4C123
 * Implementation of the 4-bit digital to analog converter
 * Authors: Daniel Valvano,
 *					Jonathan Valvano,
 * 					Thomas Royko
 * Student: Quinn Kleinfelter
 * Section: 001/003
 * Date:    11/17/2020
 *
 * Port B bits 3-0 have the 4-bit DAC
 *******************************************************************/

#include "DAC.h"
#include "..//inc//tm4c123gh6pm.h"

// **************DAC_Init*********************
// Initialize 4-bit DAC on Port B
// Input: none
// Output: none
void DAC_Init(void){
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x02;						// Enable Port B clock
	delay = SYSCTL_RCGC2_R;						// delay
	GPIO_PORTB_AMSEL_R&= ~0x7F;				// Disable analog function PB6-PB0
	GPIO_PORTB_PCTL_R &= ~0x0FFFFFFF; // Regular GPIO
	GPIO_PORTB_DIR_R |= 0x7F;					// PB3 is output
	GPIO_PORTB_AFSEL_R &= ~0x7F;			// Disable alternate functions
	GPIO_PORTB_PUR_R &= ~0x7F;				// no pullup resistors
	GPIO_PORTB_DEN_R |= 0x7F;					// Digial Enable PB6-PB0
}


// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(unsigned long data){
  
}
