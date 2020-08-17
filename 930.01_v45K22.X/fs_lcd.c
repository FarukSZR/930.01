/**
******************************************************************************
  * @file		: fs_lcd.c
  * @brief		: LCD Interface Class source file
  *				  This file contains LCD interface class
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


#include "fs_lcd.h"

/*
 * @brief  Initialize LCD  
 * @param  none
 * @return none
 */
void lcdPort(char a)
{
   if(a & 1) { D4 = 1;}    
   else {D4 = 0;}
      
   if(a & 2) { D5 = 1;}    
   else { D5 = 0;}
     
   if(a & 4) {D6 = 1;}     
   else {D6 = 0;}
      
   if(a & 8) {D7 = 1;}      
   else {D7 = 0;}
      
}



/*
 * @brief  Initialize LCD  
 * @param  none
 * @return none
 */
void lcdCmd(char a)
{
   RS = 0;             // => RS = 0
   lcdPort(a);
   EN  = 1;             // => E = 1
   __delay_ms(2);
   EN  = 0;             // => E = 0
}



/*
 * @brief  LCD Clear 
 * @param  none
 * @return none
 */
void lcdClear()
{
   lcdCmd(0);
   lcdCmd(1);
}

/*
 * @brief  Lcd Set Cursor 
 * @param  none
 * @return none
 */
void lcdSetCursor(char a, char b)
{
   char temp,z,y;
   if(a == 1)
   {
     temp = 0x80 + b - 1;
      z = temp>>4;
      y = temp & 0x0F;
      lcdCmd(z);
      lcdCmd(y);
   }
   else if(a == 2)
   {
      temp = 0xC0 + b - 1;
      z = temp>>4;
      y = temp & 0x0F;
      lcdCmd(z);
      lcdCmd(y);
   }
}

/*
 * @brief  Initialize LCD  
 * @param  none
 * @return none
 */
void lcdInit(void)
{       
    TRISDbits.RD6 = 0;
    ANSELDbits.ANSD6 = 0;
    
    TRISDbits.RD7 = 0;
    ANSELDbits.ANSD7 = 0;
    
    TRISBbits.RB0 = 0;
    ANSELBbits.ANSB0 = 0;
    
    TRISBbits.RB1 = 0;
    ANSELBbits.ANSB1 = 0;
    
    TRISBbits.RB2 = 0;
    ANSELBbits.ANSB2 = 0;
    
    TRISBbits.RB3 = 0;
    ANSELBbits.ANSB3 = 0; 
    
    
    lcdPort(0x00);
     __delay_ms(20);
    lcdCmd(0x03);
     __delay_ms(5);
    lcdCmd(0x03);
     __delay_ms(11);
    lcdCmd(0x03);
    lcdCmd(0x02);
    lcdCmd(0x02);
    lcdCmd(0x08);
    lcdCmd(0x00);
    lcdCmd(0x0C);
    lcdCmd(0x00);
    lcdCmd(0x06);
}



/*
 * @brief  Write character lcd
 * @param  none
 * @return none
 */
void lcdWriteChar(char a)
{
   char temp,y;
   temp = a&0x0F;
   y = a&0xF0;
   RS = 1;             // => RS = 1
   lcdPort(y>>4);             //Data transfer
   EN = 1;
   __delay_us(40);
   EN = 0;
   lcdPort(temp);
   EN = 1;
   __delay_us(40);
   EN = 0;
}



/*
 * @brief  Write String
 * @param  none
 * @return none
 */
void lcdWriteString(char *a)
{
   int i;
   for(i=0;a[i]!='\0';i++)
   lcdWriteChar(a[i]);
}



/*
 * @brief  Right Shift Cursor
 * @param  none
 * @return none
 */
void lcdShiftRight()
{
   lcdCmd(0x01);
   lcdCmd(0x0C);
}



/*
 * @brief  Left Shift Cursor 
 * @param  none
 * @return none
 */
void lcdShiftLeft()
{
   lcdCmd(0x01);
   lcdCmd(0x08);
}

