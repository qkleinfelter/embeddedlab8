/*******************************************************************
 * Sound.c
 * Instructor: ***fill this in***
 * Runs on TM4C123
 * Use the SysTick timer to request interrupts at a particular period.
 * Authors: Daniel Valvano,
 *					Jonathan Valvano,
 * 					Thomas Royko
 * Student: Quinn Kleinfelter
 * Section: 001/003
 * Date:    11/17/2020
 *
 * This module calls the 4-bit DAC
 *******************************************************************/

#include "Sound.h"
#include "DAC.h"
#include "..//inc//tm4c123gh6pm.h"

int up = 1;		 // Counting up or down, 1 for up, 0 for down
int count = 0; // Count variable
uint32_t pitch;

// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Also calls DAC_Init() to initialize DAC
// Input: none
// Output: none
void Sound_Init(void){
  DAC_Init();
	
	NVIC_ST_CTRL_R = 0;				// Disable SysTick during setup
	NVIC_ST_RELOAD_R = 5000;  // set reload
	NVIC_ST_CURRENT_R = 0;    // clear current
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x40000000; // priority 2
	NVIC_ST_CTRL_R = 0x07;    // enable SysTick with core clock & interrupts
	
	pitch = 0;
	
	Sound_Off();
}

// **************Sound_Tone*********************
// Change Systick periodic interrupts to start sound output
// This routine sets the RELOAD and starts SysTick
// Input: interrupt period
//           Units of period are 12.5ns
//           Maximum is 2^24-1
//           Minimum is determined by length of ISR
// Output: none
void Sound_Tone(unsigned long period){
	if (period == 0) {
		Sound_Off();
	} else {
		GPIO_PORTB_DEN_R |= 0x3F;
	}
}


// **************Sound_Off*********************
// Stop outputing to DAC
// This routine stops the sound output
// Output: none
void Sound_Off(void){
	GPIO_PORTB_DATA_R &= ~0x3F;
	GPIO_PORTB_DEN_R &= ~0x3F;
}


// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void){
	// debug monitor
	GPIO_PORTB_DATA_R |= 0x40;
	
	// toggle heartbeat
	GPIO_PORTF_DATA_R ^= 0x04;
	
	pitch = (pitch + 1) % GPIO_PORTE_DATA_R;
	if (pitch == 0) {
		DAC_Out(count);
		
		if (count == 15) {
			up = 0;
		} else if (count == 0) {
			up = 1;
		}
		
		if (up == 1) {
			count++;
		} else {
			count--;
		}
	}
	
	// turn off debug monitor
	GPIO_PORTB_DATA_R &= ~0x40;
}
