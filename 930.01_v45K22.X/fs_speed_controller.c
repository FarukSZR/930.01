/**
******************************************************************************
  * @file		: fs_speed_controller.c
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



#include "fs_speed_controller.h"
#include "fs_adc.h"
#include "fs_mcu.h"



/*
 *@brief The function that loads the respective motors speeds according to the line reference read from the ADC.
 *@param[in] position : The average value read from the ADC is written into it.
 * 
 */
void speedControl(float position)
{
    float pos = 0;
    
    pos = (float) position;
    
    controller.error = (int16_t)(position - 3400.0);
    controller.motorSpeed = (int16_t) (KP * controller.error + KD * (controller.error - controller.lastError));
    controller.lastError = controller.error;

   controller.leftMotorSpeed  =(int16_t) (DEF_SPEED + controller.motorSpeed + 70); // Bu kısımda limitin dışına çıkabilir. Left ile right limitlerini birbirinden ayırmanız gerekebilir. Deneyip gözlemleyin.
   controller.rightMotorSpeed =(int16_t) (DEF_SPEED - controller.motorSpeed);

    if (controller.leftMotorSpeed < MIN_SPEED)      // Limitler
    {
        controller.leftMotorSpeed = MIN_SPEED;
    }

    if (controller.rightMotorSpeed < MIN_SPEED)     // Limitler
    {
      controller.rightMotorSpeed = MIN_SPEED;
    }

    if (controller.leftMotorSpeed > MAX_SPEED)      // Limitler
   {
        controller.leftMotorSpeed = MAX_SPEED;
    }

    if (controller.rightMotorSpeed > MAX_SPEED)     // Limitler
    {
        controller.rightMotorSpeed = MAX_SPEED;
    }        
}



/*
 *@brief Sensorun cizgiden cikip cikmadigini kontrol eder.
 *@param none
 * 
 */
void driveSafetyCheck(void)
{
    if (START == 1)
    {
        controller.driver_safety_check = 1; 
    }
    
    if (START == 0)
    {
        controller.driver_safety_check = 0; 
    }
}