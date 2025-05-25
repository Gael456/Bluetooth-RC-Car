/**
 * @file Motor.c
 *
 * @brief Source file for the Stepper_Motor driver.
 *
 * This file contains the function definitions for the Stepper_Motor driver. It uses
 * GPIO pins to provide output signals to the ULN2003 stepper motor driver.
 * 
 * The following components are used:
 *	-	3.3V - 6V TT Motor
 *  - ULN2003 Motor Driver
 *
 * @author Gael Esparza Lobatos
 */

#include "Motor.h"

static uint16_t g_period = 16000;


void Motor_Init(uint16_t period_constant, uint16_t duty_cycle)
{
	
	g_period = period_constant;
	
	// Return from the function if the specified duty_cycle is greater than
	// or equal to the given period. The duty cycle cannot exceed 99%
	if (duty_cycle >= period_constant) return;
	
	// Enable the clock to PWM module 0 by setting th R0 bit
	// in the RCGCPWM register
	SYSCTL->RCGCPWM |= 0x01;
	

	SYSCTL->RCGCGPIO |= 0x02; // Enable GPIOB
	
	GPIOB->DIR |= 0xF0; //Set pins PB7 to PB4 as outputs
	
	GPIOB->AFSEL |= 0xF0; // Enable alternate functions
	
	GPIOB->PCTL &= ~0xFFFF0000; // Clears PCTLmfor PB4 to PB7
	
	GPIOB->PCTL |= 0x44440000; // Sets PB4 to 7 to M0PWM functions
	
	GPIOB->DEN |= 0xF0; // Enable digital function
	
	PWM0->_0_CTL &= ~0x01; // Disable generator 0
	PWM0->_1_CTL &= ~0x01; // Disable generator 1
	
	// Set the ACTcmPAD field (Bits 7 to 6) to 0x3 in the PWM0GENA register
	// to drive the PWM signal high when the counter matches
	// the comparator (i.e. the value in PWM0CMPA) while counting down
	// Front motor
	PWM0->_0_GENA |= 0x0000008C; // Set on LOAD, Clear on CMPA
	PWM0->_0_GENB |= 0x0000080C;
	
	// Rear motor
	PWM0->_1_GENA = 0x00000008C;
	PWM0->_1_GENB = 0x00000080C;
	
	// Set the period by writing to the LOAD field (Bits 15 to 0)
	// in the PWM0LOAD register. The determines the number of clock
	// cycles needed to count down to zero
	PWM0->_0_LOAD = (period_constant - 1);
	PWM0->_1_LOAD = (period_constant - 1);
	
	// Set the duty cycle by writing to the COMPA field (Bits 1 to 0)
	// in the PWM0CMPA register. When the counter matches the value in this register,
	// the PWM signal will be driven high
	PWM0->_0_CMPA = (period_constant - duty_cycle);
	PWM0->_0_CMPB = (period_constant - duty_cycle);
	
	PWM0->_1_CMPA = (period_constant - duty_cycle);
	PWM0->_1_CMPB = (period_constant - duty_cycle);
	
	
	// Enable the PWM0_0 block after configuration by setting the
	// ENABLE bit (Bit 0) in the PWM0CTL register
	PWM0->_0_CTL |= 0x01;
	PWM0->_1_CTL |= 0x01;
	
	// Enable the PWM0_0 block to be passed to the PB4, PB5, PB6, and PB7 pin (M0PWM0-M0PWM3)
	PWM0->ENABLE |= 0x0F;
	
}

void PWM0_0_Update_Duty_Cycle(uint16_t duty_cycle)
{
	// Set the duty cycle by writing to the COMPA field (Bits 15 to 0)
	// in the PW0CMPA register. When the counter matches the value in this register,
	// the PWM signal will be driven high
	PWM0->_0_CMPA = duty_cycle;
}


void Motor_Forward(uint16_t speed)
{
	if (speed >= g_period) speed = g_period - 1;
  // For Motor A (PWM generator 0): Forward direction (AIN1 active, AIN2 off)
  PWM0->_0_CMPA = g_period - speed;  // Set forward PWM duty cycle on PB6 (M0PWM0)
  PWM0->_0_CMPB = 0;      // Ensure reverse channel on PB7 (M0PWM1) is off

  // For Motor B (PWM generator 1): Forward direction (BIN1 active, BIN2 off)
  PWM0->_1_CMPA = g_period - speed;  // Set forward PWM duty cycle on PB4 (M0PWM2)
  PWM0->_1_CMPB = 0;      // Ensure reverse channel on PB5 (M0PWM3) is off
}

// High-level function to drive both motors in reverse
void Motor_Reverse(uint16_t speed)
{
  // For Motor A (PWM generator 0): Reverse direction (AIN2 active, AIN1 off)
  PWM0->_0_CMPA = 0;      // Turn off forward channel on PB6 (M0PWM0)
  PWM0->_0_CMPB = g_period - speed;  // Set reverse PWM duty cycle on PB7 (M0PWM1)

  // For Motor B (PWM generator 1): Reverse direction (BIN2 active, BIN1 off)
  PWM0->_1_CMPA = 0;      // Turn off forward channel on PB4 (M0PWM2)
  PWM0->_1_CMPB = g_period - speed;  // Set reverse PWM duty cycle on PB5 (M0PWM3)
}

// High-level function to stop both motors
void Motor_Stop(void)
{
    // For Motor A (PWM generator 0)
    PWM0->_0_CMPA = 0;
    PWM0->_0_CMPB = 0;
    
    // For Motor B (PWM generator 1)
    PWM0->_1_CMPA = 0;
    PWM0->_1_CMPB = 0;
}