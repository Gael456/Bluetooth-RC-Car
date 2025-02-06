#include "Motor.h"
#include "Timer_Interrupt.h"   // Contains Timer_0A_Interrupt_Init() and TIMER0A_Handler()
#include "TM4C123GH6PM.h"

volatile uint32_t g_msTicks = 0;

// User-defined task to be called every 1ms by Timer0A interrupt
void Timer0ATask(void)
{
    g_msTicks++;
}

// Simple delay function using the g_msTicks counter
void delay_ms(uint32_t ms)
{
    uint32_t start = g_msTicks;
    while ((g_msTicks - start) < ms)
    {
        // Busy-wait loop; consider low-power sleep in a real application.
    }
}

int main(void)
{
    
    // Initialize Timer 0A to generate an interrupt every 1ms.
    // The Timer0ATask function will increment g_msTicks.
    Timer_0A_Interrupt_Init(Timer0ATask);
    
    // Initialize the motor driver.
    // Example: period_constant = 16000 (for a specific PWM frequency), duty_cycle = 8000 (50% duty cycle)
    Motor_Init(16000, 8000);
    
    // Main test loop: cycle through motor commands.
    while (1)
    {
        // Command the motors to run forward at 50% speed
        Motor_Forward(8000);
        delay_ms(1000);  // Run forward for 1 second
        
        // Command the motors to run in reverse at 50% speed
        Motor_Reverse(8000);
        delay_ms(1000);  // Run reverse for 1 second
        
        // Stop the motors
        Motor_Stop();
        delay_ms(1000);  // Remain stopped for 1 second
    }
}