/**
******************************************************************************
  * @file		: fs_speed_controller.h
  * @brief		: Speed Controller Interface Class header file
  *				  This file contains Speed Controller interface class
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

#ifndef FS_SPEED_CONTROLLER_H
#define	FS_SPEED_CONTROLLER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "fs_lcd.h"
#include "fs_adc.h"
#include "fs_mcu.h"
#include "fs_pwm.h"    
    
static float KP =  0.5;
static float KD =  5.0;
    
#define MAX_SPEED   500
#define MIN_SPEED   300
#define DEF_SPEED   150

    
void speedControl(float position);
void stopMotor(void);
void startMotor(void);


typedef struct
{
    int16_t  error;
    int16_t  lastError;
    uint16_t motorSpeed;
    int16_t leftMotorSpeed;
    int16_t rightMotorSpeed;
    
    float left;
    float right;
   
    uint8_t driver_safety_check;
}tS_controller;


tS_controller controller;
#ifdef	__cplusplus
}
#endif

#endif	/* FS_SPEED_CONTROLLER_H */

