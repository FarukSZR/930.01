/**
******************************************************************************
  * @file		: fs_timer.c
  * @brief		: TIMER Interface Class
  *				  This file contains Timer interface class
  * @author		: Faruk Sozuer
  * @date		: 14.07.2020
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
#include "fs_timer.h"
#include "fs_menu_controller.h"




/*
 * @brief  10ms tick timer interrupt routine
 */
void __interrupt (high_priority) TIMER0 (void)
{
    if ((INTCONbits.TMR0IF)&&(INTCONbits.TMR0IE)) // Timer Interrupt Authorization bit.
    {  
        INTCONbits.TMR0IF = 0; // TMR0IF reset and preload this value.
        TMR0H	 = 0x63;
        TMR0L	 = 0xC0;
        
        timer_value.timer_0_counter++;   
        
        if(button_bounce_controller.menu == 1)
        {
             timer_value.menu_login_delay++;
        }
        else
        {
             timer_value.menu_login_delay = 0;
        }            
        
        if (timer_value.timer_0_counter >= 100) // Task scheduler is count 8
        {
            timer_value.timer_0_counter = 0;
            timer_counter_flag.one_second_flag = 1;
        }       
    }  
} 



/*
 * @brief  10ms tick timer initialize
 * @param  none
 * @return none
 */
void timer_0_init(void)
{
  T0CON	 = 0x81;
  TMR0H	 = 0x63;
  TMR0L	 = 0xC0;
  INTCONbits.GIE = 1;
  INTCONbits.TMR0IE = 1;
}
