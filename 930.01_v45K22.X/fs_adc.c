/**
******************************************************************************
  * @file		: fs_adc.c
  * @brief		: ADC Interface Class
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

#include "fs_adc.h"



/*
 * @brief Starts the ADC cycle for the selected channel.
 * @param[in] ADC channel to be read.
 * @return adcValue
 */
uint16_t readAdcValue(uint8_t adcChannel)
{
    uint16_t adcValue = 0;
      
	ADCON0bits.CHS = adcChannel;            // Select the A/D channel 	
	ADCON0bits.ADON = 1;                    // Turn on the ADC module
	ADCON0bits.GO_nDONE = 1;                // Start the conversion
	while (ADCON0bits.GO_nDONE);            // Wait for the conversion to finish 	
	adcValue = (uint16_t)((ADRESH << 8) + ADRESL);    // Conversion finished, return the result         
    return adcValue;
}



/*
 * @brief  Initialize ADC  
 * @param  none
 * @return none
 */
void adcInit(void)
{
    TRISAbits.TRISA0 = 1;      //Disable the output driver for pin RA0/AN0
    ANSELAbits.ANSA0 = 1;      //set RA0/AN0 to analog mode
    
    TRISAbits.TRISA1 = 1;      //Disable the output driver for pin RA1/AN1
    ANSELAbits.ANSA1 = 1;      //set RA1/AN1 to analog mode
    
    TRISAbits.TRISA2 = 1;      //Disable the output driver for pin RA2/AN2
    ANSELAbits.ANSA2 = 1;      //set RA2/AN2 to analog mode
    
    TRISAbits.TRISA3 = 1;      //Disable the output driver for pin RA3/AN3
    ANSELAbits.ANSA3 = 1;      //set RA3/AN3 to analog mode
     
    TRISAbits.TRISA5 = 1;      //Disable the output driver for pin RA5/AN4
    ANSELAbits.ANSA5 = 1;      //set RA5/AN4 to analog mode
    
    TRISEbits.TRISE0 = 1;      //Disable the output driver for pin RE0/AN5
    ANSELEbits.ANSE0 = 1;      //set RE0/AN5 to analog mode
        
    TRISEbits.TRISE1 = 1;      //Disable the output driver for pin RE1/AN6
    ANSELEbits.ANSE1 = 1;      //set RE1/AN6 to analog mode
    
    TRISEbits.TRISE2 = 1;      //Disable the output driver for pin RE2/AN7
    ANSELEbits.ANSE2 = 1;      //set RE2/AN7 to analog mode
    
    ADCON0 = 0x01;
    ADCON1=0x00;
	ADCON2bits.ADFM = 1;       // A/D Conversion Result Format Right justified
    ADCON2bits.ACQT = 0b010;   // 4 TAD
    ADCON2bits.ADCS = 0b110;   // FOSC/64
}



/*
 * @brief  Function that holds ADC raw data and translates. The end time of all cycles is 80ms.
 * @param  none
 * @return none
 */
void scanAdcConversion(void)
{   
    switch(timer_value.adc_conversion_time)
    {
        case 1:
            adc_raw_data.channel_0 = readAdcValue(AN0); // RA0 pin
            convert_data.convert_channel_0 = (uint16_t)((adc_raw_data.channel_0*5.0)/1024.0);
//            procces_data.channel_0 = (float)((adc_raw_data.channel_0*5.0)/1024.0);
//            convert_data.convert_channel_0 = (uint32_t)((procces_data.channel_0*999)/5);        
        break;

        case 2:
            adc_raw_data.channel_1 = readAdcValue(AN1); // RA1 pin
            convert_data.convert_channel_1 = (uint16_t)((adc_raw_data.channel_1*5.0)/1024.0);        
        break;

        case 3:
            adc_raw_data.channel_2 = readAdcValue(AN2); // RA2 pin
            convert_data.convert_channel_2 = (uint16_t)((adc_raw_data.channel_2*5.0)/1024.0);
//            procces_data.channel_2 = (float)((adc_raw_data.channel_2*5.0)/1024.0);
//            convert_data.convert_channel_2 = (uint16_t)((procces_data.channel_2*999)/5);
        break;

        case 4:
            adc_raw_data.channel_3 = readAdcValue(AN3); // RA3 pin
            convert_data.convert_channel_3 = (uint16_t)((adc_raw_data.channel_3*5.0)/1024.0);
//            procces_data.channel_3 = (float)((adc_raw_data.channel_3*5.0)/1024.0);          
//            convert_data.convert_channel_3 = (uint16_t)((procces_data.channel_3*999)/5);
        break;

        case 5:
            adc_raw_data.channel_4 = readAdcValue(AN4); // RA5 pin
            convert_data.convert_channel_4 = (uint16_t)((adc_raw_data.channel_4*5.0)/1024.0);
//            procces_data.channel_4 = (float)((adc_raw_data.channel_4*5.0)/1024.0);
//            convert_data.convert_channel_4 = (uint16_t)((procces_data.channel_4*999.0)/5.0);
        break;

        case 6:
           adc_raw_data.channel_5 = readAdcValue(AN5); // RE0 pin
           convert_data.convert_channel_5 = (uint16_t)((adc_raw_data.channel_5*5.0)/1024.0);
//           procces_data.channel_5 = (float)((adc_raw_data.channel_5*5.0)/1024.0);
//           convert_data.convert_channel_5 = (uint32_t)((procces_data.channel_5*999)/5);
        break;

        case 7:
            adc_raw_data.channel_6 = readAdcValue(AN6); // RE1 pin
            convert_data.convert_channel_6 = (uint16_t)((adc_raw_data.channel_6*5.0)/1024.0);
//            procces_data.channel_6 = (float)((adc_raw_data.channel_6*5.0)/1024.0);
//            convert_data.convert_channel_6 = (uint16_t)((procces_data.channel_6*999.0)/5.0);
        break;
        
        case 8:
            adc_raw_data.channel_7 = readAdcValue(AN7); // RE2 pin
            convert_data.convert_channel_7 = (uint16_t)((adc_raw_data.channel_7*5.0)/1024.0);
            //procces_data.channel_7 = (float)((adc_raw_data.channel_7*5.0)/1024.0);
            //convert_data.convert_channel_7 = (uint16_t)((procces_data.channel_7*999.0)/5.0);
            
        break;
    }
}


/*
 * @brief  Function that holds ADC raw data and translates. The end time of all cycles is 80ms.
 * @param  none
 * @return none
 */
void calculatedAverageValue(void)
{
    driver_limit.pay_1 = 0;
    driver_limit.payda = 0;
    driver_limit.ortalama = 0;
    
     /*Limit 27972999/7992*/
   driver_limit.pay_1 =(uint32_t) ( (convert_data.convert_channel_0 *1.0) +  
                                    (convert_data.convert_channel_1 * 1000.0) + 
                                    (convert_data.convert_channel_2 * 2000.0) + 
                                    (convert_data.convert_channel_3 * 3000.0));  
           
   driver_limit.pay_2 = (uint32_t) ( (convert_data.convert_channel_4 * 4000.0) + 
                                     (convert_data.convert_channel_5 * 5000.0) +  
                                     (convert_data.convert_channel_6 * 6000.0) +
                                     (convert_data.convert_channel_7 * 7000.0) );
   
   driver_limit.total_pay = (uint32_t)(driver_limit.pay_1+driver_limit.pay_2);
   
    driver_limit.payda = (uint32_t) (convert_data.convert_channel_0 + convert_data.convert_channel_1 + 
                                     convert_data.convert_channel_2 + convert_data.convert_channel_3 + 
                                     convert_data.convert_channel_4 + convert_data.convert_channel_5 + 
                                     convert_data.convert_channel_6 + convert_data.convert_channel_7 ) ;
    
    driver_limit.ortalama = (float)((driver_limit.total_pay/driver_limit.payda)/10.0);
}