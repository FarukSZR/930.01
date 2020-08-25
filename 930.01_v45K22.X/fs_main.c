/**
******************************************************************************
  * @file		: fs_main.c
  * @brief		: Main Interface Class source file
  *				  This file contains Main interface class
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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fs_main.h"
#include "fs_adc.h"
#include "fs_timer.h"
#include "fs_lcd.h"
#include "fs_mcu.h"
#include "fs_pwm.h"
#include "fs_speed_controller.h"
#include "fs_menu_controller.h"

__EEPROM_DATA(30,10,4,0,0,0,0,0); // DriverTime,StopTime,SpeedLimit

//#define DEBUG

#ifdef DEBUG

uint16_t i=0;
char textCursor2[16] = {0};

#endif

/*
 * @brief The function that controls which time state.
 * @param none
 * @return none
 */
void loopTaskTimeMachine(void)
{
    if (timer_counter_flag.one_second_flag == 1)
    {
        timer_counter_flag.one_second_flag = 0;
        
        if ( (startIsClick == 1) && (pauseIsClick == 0) && (stopIsClick == 0) && (menu_selected == MAIN_MENU) )
        {
            timer_value.second++;
            timer_value.remainingSecond = (uint8_t)60 - timer_value.second;
                           
            if (timer_value.remainingSecond == 59 )
            {
                timer_value.minute++;
                timer_value.remainingMinute = (int8_t)menu_value.driver_time - timer_value.minute;
            }
            
            if (timer_value.second > 59)
            {
                timer_value.second = 0;
            }
        }                   
    } 
}



/*
 * @brief   Setup function for sensor & peripheral initialization
 * @param   void Nothing
 * @return  void Nothing
 */
void loopTaskInit(void)
{
    mcuInit();     // GPIO and Clock setting initialize
    menuInitialize();
     
    adcInit();      // ADC initialize
    
    timer_0_init(); // 10ms timer initalize
    lcdInit();
    systemInit();
    lcdClear();

    PWM_Init();    //20Khz Pwm Period
    PWM1_setDC(0);
    PWM2_setDC(0);
    openLCD_Script();  
}

/*
 * @brief   CPU main function
 * @param   void Nothing
 * @return  int  Function Status
 */
void main(void) 
{
    loopTaskInit();
         
    while(1)
    {              
        loopTaskTimeMachine();   
        loopTaskMenuControl(); 
        
#ifdef DEBUG
//       if ( (startIsClick == TRUE) && (pauseIsClick == FALSE) && (stopIsClick == FALSE) )
//       {     
//            if (timer_counter_flag.one_second_flag == 1)
//            {
                  timer_counter_flag.one_second_flag = 0;
//                i += 10;
//                PWM1_setDC(i);
//                PWM2_setDC(i);
//                lcdSetCursor(1,1);
//                sprintf(textCursor2,"PWM Value= %d",i);
//                if (i>1023)
//                {
//                    i = 0;
//                }
//            }
//       }
//        
//        
//       if ( (startIsClick == FALSE) && (pauseIsClick == FALSE) && (stopIsClick == TRUE) )
//       {
//            stopMotor();
//       }
#endif
        
    } 
}
