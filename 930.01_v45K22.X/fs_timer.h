/**
******************************************************************************
  * @file		: fs_timer.h
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

#ifndef FS_TIMER_H
#define	FS_TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "fs_main.h"
    
void timer_0_init(void);


typedef struct
{    
    uint8_t one_second_flag:1;
}tS_timer_counter_flag;

typedef struct
{
    uint8_t second;
    uint8_t minute;
    uint8_t remainingSecond;
    int8_t  remainingMinute;
    uint8_t  menu_login_delay;
    uint8_t  timer_0_counter;
    uint16_t second_counter;
}tS_timer_value;

tS_timer_counter_flag timer_counter_flag = {0};
tS_timer_value        timer_value = {0};
#ifdef	__cplusplus
}
#endif

#endif	/* FS_TIMER_H */

