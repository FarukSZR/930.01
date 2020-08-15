/**
******************************************************************************
  * @file		: fs_pwm.c
  * @brief		: PWM Interface Class source file
  *				  This file contains PWM interface class
  * @author		: Faruk Sozuer
  * @date		: 28.07.2020
  * @version	: 0.0.1
 ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Faruk Sozuer, All Rights Reserved </center></h2>
  *
  * All information contained herein is, and remains the property of Faruk Sozuer. The
  * intellectual and technical concepts contained herein are proprietary to Faruk Sozuer
  * and are protected by trade secret or copyright law. Dissemination of this
  * information or reproduction of this material is strictly forbidden unless
  * prior written permission is obtained from Faruk Sozuer.  Access to the source code
  * contained herein is hereby forbidden to anyone except current Faruk Sozuer employees,
  * managers or contractors who have executed Confidentiality and Non-disclosure
  * agreements explicitly covering such access.
 ******************************************************************************
  */


#include "fs_pwm.h"


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
 