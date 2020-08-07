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

#include <proc/pic18f45k22.h>
#include "fs_menu_controller.h"
#include "fs_timer.h"
#include "fs_lcd.h"
#include "fs_eeprom.h"
#include "fs_speed_controller.h"


/*
 * @brief Initialize the I2C peripharel unit.
 * @param none
 * @return none
 */
void menuInitialize(void)
{    
    ANSELBbits.ANSB5 = 0;
    TRISBbits.RB5 = 1;  //RB3 is input pin.
    
    ANSELBbits.ANSB4 = 0;
    TRISBbits.RB4 = 1;  //RB3 is input pin.
    
    ANSELBbits.ANSB3 = 0;
    TRISBbits.RB3 = 1;  //RB3 is input pin.
    
    ANSELAbits.ANSA0 = 0;
    TRISAbits.RA0 = 1;  //RA0 is input pin.
    
    ANSELAbits.ANSA5 = 0;
    TRISAbits.RA5 = 1;  //RA5 is input pin.
    
    ANSELBbits.ANSB2 = 0;
    TRISBbits.RB2 = 1;  //RB2 is input pin.
    
    ANSELEbits.ANSE2 = 0;
    TRISEbits.RE2 = 0; // RE2 is output
    
    TRISAbits.RA4 = 0; // RA4 is output  
    TRISBbits.RB6 = 0; // RB6 is output
}



/*
 * @brief Initialize the I2C peripharel unit.
 * @param none
 * @return none
 */
void buttonControlFlags(void)
{    
    char textCursor2[16] = {0};
    
    if ((button_bounce_controller.menu == FALSE) && (BUTTON_MENU == FALSE))
    {        
        button_bounce_controller.menu = TRUE;
        menu_flags.menu_input_flag = TRUE;        
    }
   
    if ((BUTTON_MENU == TRUE) && (button_bounce_controller.menu == TRUE))
    {      
        button_bounce_controller.menu = FALSE;
        menu_flags.menu_input_flag = FALSE;
    }
             
    if ((button_bounce_controller.pause == FALSE) && (BUTTON_PAUSE == FALSE))
    {
        button_bounce_controller.pause = TRUE;
        menu_flags.menu_pause_flag = TRUE;        
    }
    if ((BUTTON_PAUSE == TRUE) && (button_bounce_controller.pause == TRUE))
    {      
        button_bounce_controller.pause = FALSE;
        menu_flags.menu_pause_flag = FALSE;
    }
    
    
    if ((button_bounce_controller.start == FALSE) && (BUTTON_START == FALSE))
    {
        button_bounce_controller.start = TRUE;
        menu_flags.menu_start_flag = TRUE;        
    }
    if ((BUTTON_START == TRUE) && (button_bounce_controller.start == TRUE))
    {      
        button_bounce_controller.start = FALSE;
        menu_flags.menu_start_flag = FALSE;
    }
    
    
    if ((button_bounce_controller.stop == FALSE) && (BUTTON_STOP == FALSE))
    {
        button_bounce_controller.stop = TRUE;
        menu_flags.menu_stop_flag = TRUE;        
    }
    if ((BUTTON_STOP == TRUE) && (button_bounce_controller.stop == TRUE))
    {      
        button_bounce_controller.stop = FALSE;
        menu_flags.menu_stop_flag = FALSE;
    }
    
    
    if ((button_bounce_controller.increase == FALSE) && (BUTTON_INCREASE == FALSE))
    {
        button_bounce_controller.increase = TRUE;
        menu_flags.menu_increase_flag = TRUE;        
    }
    if ((BUTTON_INCREASE == TRUE) && (button_bounce_controller.increase == TRUE))
    {      
        button_bounce_controller.increase = FALSE;
        menu_flags.menu_increase_flag = FALSE;
    }
    
    
    if ((button_bounce_controller.decrease == FALSE) && (BUTTON_DECREASE == FALSE))
    {
        button_bounce_controller.decrease = TRUE;
        menu_flags.menu_decrease_flag = TRUE;        
    }
    if ((BUTTON_DECREASE == TRUE) && (button_bounce_controller.decrease == TRUE))
    {      
        button_bounce_controller.decrease = FALSE;
        menu_flags.menu_decrease_flag = FALSE;
    }
}



/*
 * @brief State Machine 
 * @param none
 * @return none
 */
void menuControl(void)
{    
    buttonControlFlags();
    stateMachine();      
        
    if (menu_flags.menu_start_flag == TRUE)
    {
        menu_flags.menu_start_flag = FALSE; 
        startIsClick = 1;
        pauseIsClick = 0;       
        stopIsClick = 0;            
    }
    
        
    if (menu_flags.menu_pause_flag == TRUE)
    {
        menu_flags.menu_pause_flag = FALSE;
        pauseIsClick = 1;
        startIsClick = 0;
        stopIsClick = 0;
    }  
    
    if (menu_flags.menu_stop_flag == TRUE)
    {
        menu_flags.menu_stop_flag = FALSE;
        pauseIsClick = 0;
        startIsClick = 0;
        stopIsClick = 1;
    } 
}



/*
 * @brief Initialize the I2C peripharel unit.
 * @param none
 * @return none
 */
void stateMachine(void)
{    
    char textCursor2[16] = {0};   
    static uint8_t secretMenuCounter = 0;
    
    switch (menu_selected)
    {              
        case MAIN_MENU:       
        
            LED_RED = 0;
            LED_GREEN = 1;
            LED_BLUE = 0;
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("KALAN ZAMAN     ");    
            Lcd_Set_Cursor(2,1);
            sprintf(textCursor2,"      %d:%d   ",timer_value.remainingMinute,timer_value.remainingSecond);     
            Lcd_Write_String(textCursor2);

            if ( timer_value.menu_login_delay == MENU_TIMEOUT)
            {
                timer_value.menu_login_delay = 0;
                menu_selected = DRIVER_TIME_SETTING;               
            }

            if ((timer_value.remainingMinute <= 0) && (timer_value.remainingSecond == 0) )
            {         
                    menu_selected = STOP_MENU; 
                    timer_value.minute = 0;
            }

            if ( (startIsClick == FALSE) && (pauseIsClick == TRUE) && (stopIsClick == FALSE) && (menu_selected == MAIN_MENU))
            {
                menu_selected = PAUSE_MENU;
            }

            if ( (startIsClick == FALSE) && (pauseIsClick == FALSE) && (stopIsClick == TRUE) && (menu_selected == MAIN_MENU) )
            {
                 timer_value.remainingMinute = menu_value.driver_time;
                 timer_value.remainingSecond = 0;
                 timer_value.second = 0;
                 timer_value.minute = 0;
            }  
            //TODO:: Surus algoritmasi burada kosacak.
        
        break;
        
        case DRIVER_TIME_SETTING:
        
            LED_RED = 0;
            LED_GREEN = 0;
            LED_BLUE = 1; 

            if (menu_flags.menu_input_flag == TRUE) 
            {           
                menu_flags.menu_input_flag = 0;         
                menu_selected = STOP_TIME_SETTING;          
            }

            if ((menu_flags.menu_increase_flag == TRUE) && (menu_value.driver_time < 30))
            {
                menu_flags.menu_increase_flag = 0;
                menu_value.driver_time++;
                eepromWrite(DRIVER_TIME_MINUTE_ADDRESS,(uint8_t)menu_value.driver_time);
                timer_value.minute =0 ;
                timer_value.second = 0;
                timer_value.remainingSecond = 0; 
                timer_value.remainingMinute = menu_value.driver_time; // Her menuye giriste remainingMinute resetlemmeyecek. Sadece degisim varsa ilgili deger yazılacak.
            }

            if ((menu_flags.menu_decrease_flag == TRUE) && (menu_value.driver_time > 1))
            {
                 menu_flags.menu_decrease_flag = 0;
                 menu_value.driver_time--;
                 eepromWrite(DRIVER_TIME_MINUTE_ADDRESS,(uint8_t)menu_value.driver_time);
                 timer_value.minute =0 ;
                 timer_value.second = 0;
                 timer_value.remainingSecond = 0;
                 timer_value.remainingMinute = menu_value.driver_time; 
            }
              
                      
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("HAREKT ZAMANI dk");  
            Lcd_Set_Cursor(2,1);
            sprintf(textCursor2,"%d               ",menu_value.driver_time);
            Lcd_Write_String(textCursor2);

            if(timer_value.menu_login_delay == MENU_TIMEOUT)  // && (menu_selected == DRIVER_TIME_SETTING) )
            {
                timer_value.menu_login_delay = 0;
                menu_selected = PAUSE_MENU;                  
            }
      
        break;

        case STOP_TIME_SETTING:
        
            LED_RED = 0;
            LED_GREEN = 0;
            LED_BLUE = 1; 

            if (menu_flags.menu_input_flag == TRUE) 
            {           
                menu_flags.menu_input_flag = 0;         
                menu_selected = SPEED_LIMIT_SETTING;          
            }

            if ((menu_flags.menu_increase_flag == TRUE) && (menu_value.stop_time < 100))
            {
                menu_flags.menu_increase_flag = 0;
                menu_value.stop_time += 1;
                eepromWrite(STOP_TIME_EEPROM_ADDRESS,(uint8_t)menu_value.stop_time);
            }

            if ((menu_flags.menu_decrease_flag == TRUE) && (menu_value.stop_time > 0))
            {
                 menu_flags.menu_decrease_flag = 0;
                 menu_value.stop_time -= 1;
                 eepromWrite(STOP_TIME_EEPROM_ADDRESS,(uint8_t)menu_value.stop_time);
            }
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("DURMA ZAMANI  ms"); 
            Lcd_Set_Cursor(2,1);
            sprintf(textCursor2,"%d               ",menu_value.stop_time);
            Lcd_Write_String(textCursor2);

            if(timer_value.menu_login_delay == MENU_TIMEOUT) // && (menu_selected == STOP_TIME_SETTING) )
            {
                timer_value.menu_login_delay = 0;
                menu_selected = PAUSE_MENU;       
            }
        break;  

        case SPEED_LIMIT_SETTING:
        
            LED_RED = 0;
            LED_GREEN = 0;
            LED_BLUE = 1; 

            if (menu_flags.menu_input_flag == TRUE) 
            {           
                menu_flags.menu_input_flag = FALSE;         
                menu_selected = DRIVER_TIME_SETTING;          
            }

            if ((menu_flags.menu_increase_flag == TRUE) && (menu_value.speed_limit < 5))
            {
                menu_flags.menu_increase_flag = FALSE;
                menu_value.speed_limit += 1;
                eepromWrite(SPEED_LIMIT_EEPROM_ADDRESS,menu_value.speed_limit);
            }

            if ((menu_flags.menu_decrease_flag == TRUE) && (menu_value.speed_limit > 0))
            {
                 menu_flags.menu_decrease_flag = FALSE;
                 menu_value.speed_limit -= 1;
                 eepromWrite(SPEED_LIMIT_EEPROM_ADDRESS,menu_value.speed_limit);
            }
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("HIZ LiMiTi      "); 
            Lcd_Set_Cursor(2,1);
            sprintf(textCursor2,"%d               ",menu_value.speed_limit);
            Lcd_Write_String(textCursor2);

            if(timer_value.menu_login_delay == MENU_TIMEOUT)// && (menu_selected == SPEED_LIMIT_SETTING) )
            {
                timer_value.menu_login_delay = 0;
                menu_selected = PAUSE_MENU;       
            }
        break;
        
        case STOP_MENU:            
            startIsClick = 0;
            pauseIsClick = 0;
            stopIsClick = 1;

            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("ZAMAN DOLDU     "); 
            LED_RED = 1;
            LED_BLUE = 0;
            LED_GREEN = 0;
            timer_value.remainingSecond = 0;
            timer_value.remainingMinute = 0;
             Lcd_Set_Cursor(2,1);
            sprintf(textCursor2,"      %d:%d    ",timer_value.remainingMinute,timer_value.remainingSecond);
            Lcd_Write_String(textCursor2);
            
        if (menu_flags.menu_start_flag == TRUE)
        {           
            menu_flags.menu_start_flag = FALSE;         
            menu_selected = START_MENU;  
            
            startIsClick = 1; 
            pauseIsClick = 0;  
            stopIsClick = 0;
            timer_value.second = 0;
            timer_value.minute = 0; 
        } 
                       
        if ( timer_value.menu_login_delay == MENU_TIMEOUT)
        {
            timer_value.menu_login_delay = 0;
            menu_selected = DRIVER_TIME_SETTING;               
        }
        //TODO: Rampa ile durma burada olacak. 
       break;
       
        case START_MENU:          
            timer_value.remainingMinute = menu_value.driver_time;
            timer_value.remainingSecond = 0; 
            startIsClick = 1;
            stopIsClick = 0;           
            menu_selected = MAIN_MENU;
        break;
        
        case PAUSE_MENU:
          
            LED_RED = 1;
            LED_GREEN = 1;
            LED_BLUE = 1; 
            timer_value.remainingMinute = timer_value.remainingMinute;
            timer_value.remainingSecond = timer_value.remainingSecond;   
        
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("HAREKET DURDU   ");  
            Lcd_Set_Cursor(2,1);
            sprintf(textCursor2,"      %d:%d    ",timer_value.remainingMinute,timer_value.remainingSecond);
            Lcd_Write_String(textCursor2); 
               
            if (menu_flags.menu_start_flag == TRUE) 
            {           
                menu_flags.menu_start_flag = FALSE;         
                menu_selected = MAIN_MENU;  
            
                startIsClick = TRUE; 
                pauseIsClick = FALSE;  
                stopIsClick = FALSE;
            }  
                            
            if ( (startIsClick == FALSE) && (pauseIsClick == FALSE) && (stopIsClick == TRUE) && (menu_selected == PAUSE_MENU))
            {
                 timer_value.remainingMinute = menu_value.driver_time;
                 timer_value.remainingSecond = 0;
                 timer_value.second = 0;
                 timer_value.minute = 0;

            }  

            if ( timer_value.menu_login_delay == MENU_TIMEOUT)
            {
                timer_value.menu_login_delay = 0;
                menu_selected = DRIVER_TIME_SETTING;               
            }
            
            if ((menu_flags.menu_increase_flag == 1) && (menu_flags.menu_decrease_flag == 1))
            {
                menu_selected = SECRET_MENU;
                secretMenuCounter = 1;
            }
            //TODO: Rampa ile durma burada olacak.
        
        break;
        
        case EXIT_LINE:
            //TODO: Rampa ile durma burada olacak.
        break;
       
        case SECRET_MENU:
                                              
            if (menu_flags.menu_input_flag == 1)
            {
                menu_flags.menu_input_flag = FALSE;
                secretMenuCounter++;
                
                if (secretMenuCounter >2)
                {
                    secretMenuCounter = 1;
                }
            }
            
            if (secretMenuCounter == 1)
            {
                Lcd_Set_Cursor(1,1);
                Lcd_Write_String("PID PARAM       ");  
                Lcd_Set_Cursor(2,1);
                sprintf(textCursor2,"Kp:%5.1f     ",KP);
                Lcd_Write_String(textCursor2); 
                
                if ((menu_flags.menu_increase_flag == TRUE) && (KP < 2.5))
                {
                    menu_flags.menu_increase_flag = FALSE;
                    KP += 0.1;          
                }

                if ((menu_flags.menu_decrease_flag == TRUE) && (KP >= 0))
                {
                    menu_flags.menu_decrease_flag = FALSE;
                     KP -= 0.1;               
                }
            }
            
            if (secretMenuCounter == 2)
            {
                Lcd_Set_Cursor(1,1);
                Lcd_Write_String("PID PARAM       ");  
                Lcd_Set_Cursor(2,1);
                sprintf(textCursor2,"Kd:%5.1f    ",KD);
                Lcd_Write_String(textCursor2);
                               
                if ((menu_flags.menu_increase_flag == TRUE) && (KD < 2.5))
                {
                    menu_flags.menu_increase_flag = FALSE;
                    KD += 0.1;          
                }

                if ((menu_flags.menu_decrease_flag == TRUE) && (KD >= 0))
                {
                    menu_flags.menu_decrease_flag = FALSE;
                     KD -= 0.1;               
                }
            }          
            
            if ( timer_value.menu_login_delay == MENU_TIMEOUT)
            {
                timer_value.menu_login_delay = 0;
                menu_selected = PAUSE_MENU;               
            }
            
        break;
    }                    
}
