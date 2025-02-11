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
 *  - DRV8833 Motor Driver
 *
 * @author Gael Esparza Lobatos
 */

#include "TM4C123GH6PM.h"

/**
 * @brief Initializes GPIO pins required for controlling the stepper motor.
 *
 * @param Configure the necessary GPIO pins as outputs and sets them up as digital
 * functionality to control the motor through the connected motor driver.
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

/**
 * @brief Sets the PWM duty cycle to move the motors foward
 *
 * @param 
 *
 * @return None
 */
void Motor_Forward(uint16_t speed);


/**
 * @brief 
 *
 * @param 
 *
 * @return None
 */


/**
 * @brief 
 *
 * @param 
 *
 * @return None
 */
void Motor_Reverse(uint16_t speed);


/**
 * @brief 
 *
 * @param 
 *
 * @return None
 */
void Motor_Stop(void);