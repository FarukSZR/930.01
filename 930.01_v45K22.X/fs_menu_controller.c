/**
******************************************************************************
  * @file		: fs_menu_controller.c
  * @brief		: Menu Controller Interface Class source file
  *				This file contains menu controller state machine interface class
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


#include "fs_menu_controller.h"



/*
 * @brief Pin configurations of button connections.
 * @param none
 * @return none
 */
void menuInitialize(void)
{    
    //ANSELBbits.ANSB6 = 0;
    TRISBbits.RB6 = 1;  //RB3 is input pin.
    
    //ANSELBbits.ANSB7 = 0;
    TRISBbits.RB7 = 1;  //RB3 is input pin.
    
    ANSELDbits.ANSD4 = 0;
    TRISDbits.RD4 = 1;  //RB3 is input pin.
    
    ANSELDbits.ANSD0 = 0;
    TRISDbits.RD0 = 1;  //RA0 is input pin.
    
    ANSELDbits.ANSD1 = 0;
    TRISDbits.RD1 = 1;  //RA5 is input pin.
    
    ANSELDbits.ANSD2 = 0;
    TRISDbits.RD2 = 1;  //RB2 is input pin.
    
    ANSELDbits.ANSD3 = 0; //Acil Stop
    TRISDbits.RD3 = 1; // RE2 is output
    
    ANSELDbits.ANSD5 = 0;   // MP3_PLAYER
    TRISDbits.RD5 = 0;      // RD5 is output
    
    ANSELCbits.ANSC5 = 0;  // COMM OUTPUT
    TRISCbits.RC5 = 0;     // RC5 is output
    
    ANSELCbits.ANSC4 = 0;  // LAMB OUTPUT
    TRISCbits.RC4 = 0;     // RC4 is output
    
}



/*
 * @brief The variable that controls the falling edge, rising edge status of the buttons.
 * @param none
 * @return none
 */
void buttonControlFlags(void)
{       
    // Menu Click
    if ((button_bounce_controller.menu == FALSE) && (BUTTON_MENU == FALSE)) // Active Low
    {        
        button_bounce_controller.menu = TRUE;
        menu_flags.menu_input_flag = TRUE;        
    }
   
    if ((BUTTON_MENU == TRUE) && (button_bounce_controller.menu == TRUE))
    {      
        button_bounce_controller.menu = FALSE;
        menu_flags.menu_input_flag = FALSE;
    }
             
    // Pause Click
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
    
    // Start Click
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
    
    // Stop Click
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
    
    // Increase Click
    if ((button_bounce_controller.increase == FALSE) && (BUTTON_INCREASE == FALSE)) // Active Low
    {
        button_bounce_controller.increase = TRUE;
        menu_flags.menu_increase_flag = TRUE;        
    }
    if ((BUTTON_INCREASE == TRUE) && (button_bounce_controller.increase == TRUE))
    {      
        button_bounce_controller.increase = FALSE;
        menu_flags.menu_increase_flag = FALSE;
    }
    
    // Decrease Click
    if ((button_bounce_controller.decrease == FALSE) && (BUTTON_DECREASE == FALSE)) // Active Low
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
 * @brief The function that controls which button is pressed.
 * @param none
 * @return none
 */
void loopTaskMenuControl(void)
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
 * @brief State Machine function.
 * @param none
 * @return none
 */
void stateMachine(void)
{                
    switch (menu_selected)
    {              
        case MAIN_MENU:                               
            mainMenu();//TODO:: Surus algoritmasi burada kosacak.        
        break;
        
        case DRIVER_TIME_SETTING:
            driverTimeSettingMenu();                
        break;

        case STOP_TIME_SETTING:
            stopTimeSettingMenu();
        break;  

        case SPEED_LIMIT_SETTING:
            speedLimitSettingMenu();
        break;
        
        case STOP_MENU:                        
            stopMenu();         //TODO: Rampa ile durma burada olacak.      
        break;
       
        case START_MENU:          
            startMenu();       
        break;
        
        case PAUSE_MENU:
            pauseMenu();//TODO: Rampa ile durma burada olacak.        
        break;
        
        case EXIT_LINE:
            exitLine();//TODO: Rampa ile durma burada olacak. Çizgiden çıktıgında bu durma islemi gerceklestirilecek.
        break;
       
        case SECRET_MENU:
            secretMenu();       
        break;
    }                    
}



/*
 * @brief State function used to set the Main Menu.
 * @param none
 * @return none
 */
void mainMenu(void)
{
    char textCursor2[16] = {0};
    
//    lcdSetCursor(1,1);
//    lcdWriteString("KALAN ZAMAN     ");    
//    lcdSetCursor(2,1);
//    sprintf(textCursor2,"      %d:%d   ",timer_value.remainingMinute,timer_value.remainingSecond);     
//    lcdWriteString(textCursor2);

    if ( timer_value.menu_login_delay == MENU_TIMEOUT)
    {
        button_bounce_controller.menu = false;
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
        MP3_PLAYER = 0;
        COMMUNICATION_SIGNAL = 0;
        LAMB_OUTPUT = 0;
        startIsClick = 0;
    }

    if ( (startIsClick == FALSE) && (pauseIsClick == FALSE) && (stopIsClick == TRUE) && (menu_selected == MAIN_MENU) )
    {
         timer_value.remainingMinute = menu_value.driver_time;
         timer_value.remainingSecond =  0;
         timer_value.second = 0;
         timer_value.minute = 0;
         MP3_PLAYER = 0;
         COMMUNICATION_SIGNAL = 0;
         LAMB_OUTPUT = 0;
         stopMotor();
    }  

    if ( (startIsClick == TRUE) && (pauseIsClick == FALSE) && (stopIsClick == FALSE) )
    {
        startMotor();
        MP3_PLAYER = 1;
        COMMUNICATION_SIGNAL = 1;
        LAMB_OUTPUT = 1;
    }
    else
    {
        stopMotor();
        lcdClear();
        convert_data.convert_channel_0 = 0;
        convert_data.convert_channel_1 = 0;
        convert_data.convert_channel_2 = 0;
        convert_data.convert_channel_3 = 0;
        convert_data.convert_channel_4 = 0;
        convert_data.convert_channel_5 = 0;
        convert_data.convert_channel_6 = 0;
        convert_data.convert_channel_7 = 0;
    }
}



/*
 * @brief State function used to set the Stop Menu.
 * @param none
 * @return none
 */
void stopMenu(void)
{
    char textCursor2[16] = {0};
    
    stopMotor();
    
    startIsClick = 0;
    pauseIsClick = 0;
    stopIsClick = 1;

    lcdSetCursor(1,1);
    lcdWriteString("ZAMAN DOLDU     "); 

    timer_value.remainingSecond = 0;
    timer_value.remainingMinute = 0;

//    lcdSetCursor(2,1);
//    sprintf(textCursor2,"      %d:%d    ",timer_value.remainingMinute,timer_value.remainingSecond);
//    lcdWriteString(textCursor2);

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
        button_bounce_controller.menu = false;
        timer_value.menu_login_delay = 0;
        menu_selected = DRIVER_TIME_SETTING;               
    }
    
}



/*
 * @brief State function used to set the Pause Menu.
 * @param none
 * @return none
 */
void pauseMenu(void)
{
    char textCursor2[16] = {0};
    
    startIsClick = FALSE;
    timer_value.remainingMinute = timer_value.remainingMinute;
    timer_value.remainingSecond = timer_value.remainingSecond;   
    
    stopMotor();
    
//    lcdSetCursor(1,1);
//    lcdWriteString("HAREKET DURDU   ");  
//    lcdSetCursor(2,1);
//    sprintf(textCursor2,"      %d:%d    ",timer_value.remainingMinute,timer_value.remainingSecond);
//    lcdWriteString(textCursor2); 

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
        button_bounce_controller.menu = false;
        timer_value.menu_login_delay = 0;
        menu_selected = DRIVER_TIME_SETTING;               
    }

    if ((menu_flags.menu_increase_flag == 1) && (menu_flags.menu_decrease_flag == 1))
    {
        menu_selected = SECRET_MENU;
        secretMenuCounter = 1;
    }   
}



/*
 * @brief State function used to set the Start menu.
 * @param none
 * @return none
 */
void startMenu(void)
{
    timer_value.remainingMinute = menu_value.driver_time;
    timer_value.remainingSecond = 0; 
    startIsClick = 1;
    stopIsClick = 0;           
    menu_selected = MAIN_MENU; 
}


/*
 * @brief State function used to set the Secret Menu.
 * @param none
 * @return none
 */
void secretMenu(void)
{ 
    char textCursor2[16] = {0};
    
    stopMotor();      

    if (menu_flags.menu_input_flag == 1)
    {
        menu_flags.menu_input_flag = FALSE;
        secretMenuCounter++;

        if (secretMenuCounter >2)
        {
            secretMenuCounter = 1;
        }
    }

    if (secretMenuCounter == 1) // Kp parameter active
    {
        lcdSetCursor(1,1);
        lcdWriteString("PID PARAM       ");  
        lcdSetCursor(2,1);
        sprintf(textCursor2,"Kp:%5.1f     ",KP);
        lcdWriteString(textCursor2); 

        if ((menu_flags.menu_increase_flag == TRUE) && (KP < 10.0))
        {
            menu_flags.menu_increase_flag = FALSE;
            KP += 0.01;          
        }

        if ((menu_flags.menu_decrease_flag == TRUE) && (KP >= 0))
        {
            menu_flags.menu_decrease_flag = FALSE;
             KP -= 0.01;               
        }
    }

    if (secretMenuCounter == 2) // Kd parameter active
    {
        lcdSetCursor(1,1);
        lcdWriteString("PID PARAM       ");  
        lcdSetCursor(2,1);
        sprintf(textCursor2,"Kd:%5.1f    ",KD);
        lcdWriteString(textCursor2);

        if ((menu_flags.menu_increase_flag == TRUE) && (KD < 10.0))
        {
            menu_flags.menu_increase_flag = FALSE;
            KD += 0.01;          
        }

        if ((menu_flags.menu_decrease_flag == TRUE) && (KD >= 0))
        {
            menu_flags.menu_decrease_flag = FALSE;
             KD -= 0.01;               
        }
    }          

    if ( timer_value.menu_login_delay == MENU_TIMEOUT)
    {
        button_bounce_controller.menu = false;
        timer_value.menu_login_delay = 0;
        menu_selected = PAUSE_MENU;               
    }    
}


/*
 * @brief State function used to set the Speed Limit.
 * @param none
 * @return none
 */
void speedLimitSettingMenu(void)
{
    char textCursor2[16] = {0};
    stopMotor();

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

    if ((menu_flags.menu_decrease_flag == TRUE) && (menu_value.speed_limit > 1))
    {
         menu_flags.menu_decrease_flag = FALSE;
         menu_value.speed_limit -= 1;
         eepromWrite(SPEED_LIMIT_EEPROM_ADDRESS,menu_value.speed_limit);
    }
    lcdSetCursor(1,1);
    lcdWriteString("HIZ LiMiTi      "); 
    lcdSetCursor(2,1);
    sprintf(textCursor2,"%d               ",menu_value.speed_limit);
    lcdWriteString(textCursor2);

    if(timer_value.menu_login_delay == MENU_TIMEOUT)// && (menu_selected == SPEED_LIMIT_SETTING) )
    {
        button_bounce_controller.menu = false;
        timer_value.menu_login_delay = 0;
        menu_selected = PAUSE_MENU;       
    }  
}


/*
 * @brief State function used to set the Stop Time.
 * @param none
 * @return none
 */
void stopTimeSettingMenu(void)
{
    char textCursor2[16] = {0};
    
    stopMotor();

    if (menu_flags.menu_input_flag == TRUE) 
    {           
        menu_flags.menu_input_flag = 0;         
        menu_selected = SPEED_LIMIT_SETTING;          
    }

    if ((menu_flags.menu_increase_flag == TRUE) && (menu_value.stop_time < 250))
    {
        menu_flags.menu_increase_flag = 0;
        menu_value.stop_time += 10;
        eepromWrite(STOP_TIME_EEPROM_ADDRESS,(uint8_t)menu_value.stop_time);
    }

    if ((menu_flags.menu_decrease_flag == TRUE) && (menu_value.stop_time > 10))
    {
         menu_flags.menu_decrease_flag = 0;
         menu_value.stop_time -= 10;
         eepromWrite(STOP_TIME_EEPROM_ADDRESS,(uint8_t)menu_value.stop_time);
    }
    lcdSetCursor(1,1);
    lcdWriteString("DURMA ZAMANI  ms"); 
    lcdSetCursor(2,1);
    sprintf(textCursor2,"%d             ",menu_value.stop_time);
    lcdWriteString(textCursor2);

    if(timer_value.menu_login_delay == MENU_TIMEOUT) // && (menu_selected == STOP_TIME_SETTING) )
    {
        button_bounce_controller.menu = false;
        timer_value.menu_login_delay = 0;
        menu_selected = PAUSE_MENU;       
    }
}



/*
 * @brief State function used to set the Driver Time.
 * @param none
 * @return none
 */
void driverTimeSettingMenu(void)
{
    char textCursor2[16] = {0};
    
    stopMotor();                  
            
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

    if ((menu_flags.menu_decrease_flag == TRUE) && (menu_value.driver_time > 0))
    {
         menu_flags.menu_decrease_flag = 0;
         menu_value.driver_time--;
         eepromWrite(DRIVER_TIME_MINUTE_ADDRESS,(uint8_t)menu_value.driver_time);
         timer_value.minute =0 ;
         timer_value.second = 0;
         timer_value.remainingSecond = 0;
         timer_value.remainingMinute = menu_value.driver_time; 
    }                                  
    lcdSetCursor(1,1);
    lcdWriteString("HAREKT ZAMANI dk");  
    lcdSetCursor(2,1);
    sprintf(textCursor2,"%d               ",menu_value.driver_time);
    lcdWriteString(textCursor2);

    if(timer_value.menu_login_delay == MENU_TIMEOUT)  // && (menu_selected == DRIVER_TIME_SETTING) )
    {
        button_bounce_controller.menu = false;
        timer_value.menu_login_delay = 0;
        menu_selected = PAUSE_MENU;                  
    }   
}



/*
 * @brief State function used to set the Exit Line.
 * @param none
 * @return none
 */
void exitLine(void)
{
    
}