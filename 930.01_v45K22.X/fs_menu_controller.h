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

#ifndef FS_MENU_CONTROLLER_H
#define	FS_MENU_CONTROLLER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "fs_main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

    
#define LAMB_OUTPUT             LATCbits.LATC4 
#define MP3_PLAYER              LATDbits.LATD5
#define COMMUNICATION_SIGNAL    LATCbits.LATC5

#define BUTTON_PAUSE    PORTDbits.RD2
#define BUTTON_START    PORTDbits.RD0
#define BUTTON_STOP     PORTDbits.RD1
#define BUTTON_MENU     PORTBbits.RB7    
#define BUTTON_INCREASE PORTBbits.RB6 //BUTTON_INCREASE
#define BUTTON_DECREASE PORTDbits.RD4 //BUTTON_DECREASE
    
#define MENU_TIMEOUT    100
#define START_TIMEOUT   100
    
    
#define TRUE    1
#define FALSE   0
    
uint8_t  pauseIsClick = 0;
uint8_t  startIsClick = 0;
uint8_t  stopIsClick = 0; 

typedef struct
{
    uint8_t menu_input_flag :1;
    uint8_t menu_start_flag :1;
    uint8_t menu_stop_flag  :1;
    uint8_t menu_pause_flag :1;
    uint8_t menu_increase_flag :1;
    uint8_t menu_decrease_flag :1;
}tS_menu_flags;
    
typedef struct
{
    uint8_t menu     :1;
    uint8_t start    :1;
    uint8_t stop     :1;
    uint8_t pause    :1;
    uint8_t decrease :1;
    uint8_t increase :1;
}tS_button_bounce_controller;


typedef enum
{ 
    MAIN_MENU,
    DRIVER_TIME_SETTING,        // Sürüş süresi
    STOP_TIME_SETTING,          // Arac cizgiden çıktığında durması gereken süre
    SPEED_LIMIT_SETTING,
    STOP_MENU,
    START_MENU,
    PAUSE_MENU,
    EXIT_LINE,
    SECRET_MENU,
}tE_menu_selected;
    
typedef struct
{
    uint8_t driver_time;
    uint8_t stop_time;
    uint8_t speed_limit;
}tS_menu_value;


tS_button_bounce_controller button_bounce_controller = {0};
tE_menu_selected            menu_selected = {0};
tS_menu_flags               menu_flags   = {0};
tS_menu_value               menu_value   = {0};
void menuInitialize(void);
void menuControl(void);
void buttonControlFlags(void);
void stateMachine(void);
void mainMenu(void);
void stopMenu(void);
void pauseMenu(void);
void startMenu(void);

#ifdef	__cplusplus
}
#endif

#endif	/* FS_MENU_CONTROLLER_H */

