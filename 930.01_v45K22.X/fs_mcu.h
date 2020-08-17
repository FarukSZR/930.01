/**
******************************************************************************
  * @file		: fs_mcu.h
  * @brief		: Init Value Setting Interface Class header file
  *				  This file contains adc interface class
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

#ifndef GPIO_H
#define	GPIO_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <proc/pic18f45k22.h>
#include "fs_adc.h"
#include "fs_speed_controller.h"
#include "fs_timer.h"
#include "fs_menu_controller.h"
#include "fs_eeprom.h"
#include "fs_main.h"
#include "fs_lcd.h"
    
void mcuInit(void);
void systemInit(void);
void openLCD_Script(void);

#ifdef	__cplusplus
}
#endif

#endif	/* GPIO_H */

