/**
******************************************************************************
  * @file		: fs_lcd.h
  * @brief		: LCD Interface Class header file
  *				  This file contains lcd interface class
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

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

    
#include <proc/pic18f45k22.h>
#include "fs_mcu.h"
#include "fs_main.h"
    
#define TIRTIL
    
#ifdef GIYOTIN   
    #define RS PORTDbits.RD6
    #define EN PORTDbits.RD7 
    #define D4 PORTBbits.RB0
    #define D5 PORTBbits.RB1
    #define D6 PORTBbits.RB2
    #define D7 PORTBbits.RB3
#endif
  
#ifdef TIRTIL
    #define RS PORTDbits.RD6
    #define EN PORTDbits.RD7 
    #define D4 PORTBbits.RB0
    #define D5 PORTBbits.RB1
    #define D6 PORTBbits.RB2
    #define D7 PORTBbits.RB3
#endif
    
void lcdPort(char a);
void lcdCmd(char a);
void lcdClear(void);
void lcdSetCursor(char a, char b);
void lcdInit(void);
void lcdWriteChar(char a);
void lcdWriteString(char *a);
void lcdShiftRight(void);
void lcdShiftLeft(void);


#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

