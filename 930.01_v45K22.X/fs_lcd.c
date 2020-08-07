#include <xc.h>
#include <proc/pic18f45k22.h>
#include "fs_mcu.h"
#include "fs_main.h"
#include "fs_lcd.h"

/*
 * @brief  Initialize ADC  
 * @param  none
 * @return none
 */
void Lcd_Port(char a)
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

void Lcd_Cmd(char a)
{
   RS = 0;             // => RS = 0
   Lcd_Port(a);
   EN  = 1;             // => E = 1
   __delay_ms(2);
   EN  = 0;             // => E = 0
}

/*
 * @brief  Initialize ADC  
 * @param  none
 * @return none
 */
void Lcd_Clear()
{
   Lcd_Cmd(0);
   Lcd_Cmd(1);
}

/*
 * @brief  Initialize ADC  
 * @param  none
 * @return none
 */
void Lcd_Set_Cursor(char a, char b)
{
   char temp,z,y;
   if(a == 1)
   {
     temp = 0x80 + b - 1;
      z = temp>>4;
      y = temp & 0x0F;
      Lcd_Cmd(z);
      Lcd_Cmd(y);
   }
   else if(a == 2)
   {
      temp = 0xC0 + b - 1;
      z = temp>>4;
      y = temp & 0x0F;
      Lcd_Cmd(z);
      Lcd_Cmd(y);
   }
}

/*
 * @brief  Initialize ADC  
 * @param  none
 * @return none
 */
void lcd_init(void)
{       
    TRISEbits.RE0 = 0;
    ANSELEbits.ANSE0 = 0;
    
    TRISAbits.RA3 = 0;
    ANSELAbits.ANSA3 = 0;
    
    TRISDbits.RD0 = 0;
    ANSELDbits.ANSD0 = 0;
    
    TRISDbits.RD1 = 0;
    ANSELDbits.ANSD1 = 0;
    
    TRISDbits.RD2 = 0;
    ANSELDbits.ANSD2 = 0;
    
    TRISDbits.RD3 = 0;
    ANSELDbits.ANSD3 = 0; 
    
    
    Lcd_Port(0x00);
     __delay_ms(20);
    Lcd_Cmd(0x03);
     __delay_ms(5);
    Lcd_Cmd(0x03);
     __delay_ms(11);
    Lcd_Cmd(0x03);
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x08);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x0C);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x06);
}



/*
 * @brief  Initialize ADC  
 * @param  none
 * @return none
 */
void Lcd_Write_Char(char a)
{
   char temp,y;
   temp = a&0x0F;
   y = a&0xF0;
   RS = 1;             // => RS = 1
   Lcd_Port(y>>4);             //Data transfer
   EN = 1;
   __delay_us(30);
   EN = 0;
   Lcd_Port(temp);
   EN = 1;
   __delay_us(25);
   EN = 0;
}



/*
 * @brief  Initialize ADC  
 * @param  none
 * @return none
 */
void Lcd_Write_String(char *a)
{
   int i;
   for(i=0;a[i]!='\0';i++)
   Lcd_Write_Char(a[i]);
}



/*
 * @brief  Initialize ADC  
 * @param  none
 * @return none
 */
void Lcd_Shift_Right()
{
   Lcd_Cmd(0x01);
   Lcd_Cmd(0x0C);
}



/*
 * @brief  Initialize ADC  
 * @param  none
 * @return none
 */
void Lcd_Shift_Left()
{
   Lcd_Cmd(0x01);
   Lcd_Cmd(0x08);
}

