/**
******************************************************************************
  * @file		: fs_eeprom.h
  * @brief		: EEPROM Interface Class header file
  *				  This file contains eeprom interface class
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

#ifndef FS_EEPROM_H
#define	FS_EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <proc/pic18f45k22.h>
    
#define DRIVER_TIME_MINUTE_ADDRESS  0x00
#define STOP_TIME_EEPROM_ADDRESS    0x01
#define SPEED_LIMIT_EEPROM_ADDRESS  0x02
#define KP_LIMIT_EEPROM_ADDRESS     0x03
#define KD_LIMIT_EEPROM_ADDRESS     0x04
    
    
uint8_t eepromRead(uint8_t address);
void eepromWrite(uint8_t address, uint8_t data);
#ifdef	__cplusplus
}
#endif

#endif	/* FS_EEPROM_H */

