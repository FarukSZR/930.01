/**
******************************************************************************
  * @file		: fs_i2c.c
  * @brief		: I2C Interface Class
  *				  This file contains adc interface class
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

#ifndef FS_PWM_H
#define	FS_PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

  
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <proc/pic18f45k22.h>
#include <math.h>
#include "fs_mcu.h"
#include "fs_main.h"
    
    
void PWM_Init(void);    
void PWM1_setDC(int16_t dutycycle);
void PWM2_setDC(int16_t dutycycle);

#ifdef	__cplusplus
}
#endif

#endif	/* FS_PWM_H */

