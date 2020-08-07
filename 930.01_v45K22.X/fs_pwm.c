

#include <xc.h>
#include "fs_mcu.h"
#include "fs_main.h"
#include "fs_pwm.h"
#include <pic18f45k22.h>
#include <math.h>

/*
 *@brief
 *@param[in] period: Pwm Period in Hz. For example 20Khz = 20000
 * 
 */
void PWM_Init(void)
{           
    TRISCbits.RC2 = 0;                  //  Set RC2 as output  // CCP1
    TRISCbits.RC1 = 0;                  //  Set RC1 as output  // CCP2          
    
    /* CCP1 PWM mode */
    CCP1CON = 0b00001100;   // Enable PWM on CCP1      
    /* CCP2 PWM mode */
    CCP2CON = 0b00001100;   // Enable PWM on CCP2
    
    
    /* Timer2 configuration */
    T2CONbits.T2CKPS = 0b01;    // Prescler 4
    T2CONbits.TMR2ON = 1;            //  timer2 on
 
    TMR2 = 0;
    PR2 = 199;   // PWM period = 20kHz
    CCPR1L = 0; // pulse width = CCPR1L * prescaler * Tcy = 100us
    CCPR2L = 0;
}
 

/*
 * @brief set duty cycle 0 - 1023 range 
 */
void PWM1_setDC(int16_t dutycycle)
{
    uint16_t duty=0;
    
    if (dutycycle <= 1023)
    {
        duty = (uint16_t) fabs(dutycycle);   
        CCPR1L = duty>>2;  //  PWM duty cycle - first 8-bits (MSb)
    }    
}

/*
 * @brief set duty cycle 0 - 1023 range 
 */
void PWM2_setDC(int16_t dutycycle)
{
    uint16_t duty=0;
    
    if (dutycycle <= 1023)
    {
        duty = (uint16_t) fabs(dutycycle);    
        CCPR2L = duty>>2;  //  PWM duty cycle - first 8-bits (MSb) 
    }     
}
 