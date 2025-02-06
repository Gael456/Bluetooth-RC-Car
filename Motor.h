/**
 * @file Motor.h
 *
 * @brief Header file for the Motor driver.
 *
 * This file contains the function definitions for the Stepper_Motor driver. It uses
 * GPIO pins to provide output signals to the ULN2003 stepper motor driver.
 * 
 * The following components are used:
 *	-	3V-6V TT Motor
 *  - ULN2003 Stepper Motor Driver
 *  - 3.3V / 5V Breadboard Power Supply Module (External Power Source)
 *
 * @author Gael Esparza Lobatos
 */

#include "TM4C123GH6PM.h"

/**
 * @brief Initializes GPIO pins required for controlling the stepper motor.
 *
 * @param Configure the necessary GPIO pins as outputsand sets them up as digital
 * functionality to control the stepper motor through the connected motor driver.
 *
 * @return None
 */
void Motor_Init(uint16_t period_constant, uint16_t duty_cycle);


/**
 * @brief 
 *
 * @param 
 *
 * @return None
 */
void PWM0_0_Update_Duty_Cycle(uint16_t duty_cycle);

void Motor_Forward(uint16_t speed);

void Motor_Reverse(uint16_t speed);

void Motor_Stop(void);