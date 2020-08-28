/**
******************************************************************************
  * @file		: fs_adc.h
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


#ifndef FS_ADC_H
#define	FS_ADC_H

#ifdef	__cplusplus
extern "C" {
#endif
 
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "fs_timer.h"
    
#define AN0    0
#define AN1    1   
#define AN2    2
#define AN3    3 
#define AN4    4
#define AN5    5 
#define AN6    6
#define AN7    7
#define AN8    8
#define AN9    9
#define AN10   10
    

void adcInit(void);
void scanAdcConversion(void);
uint16_t readAdcValue(uint8_t adcChannel);
void calculatedAverageValue(void);

typedef struct
{
    uint16_t channel_0;
    uint16_t channel_1;
    uint16_t channel_2;
    uint16_t channel_3;
    uint16_t channel_4;
    uint16_t channel_5;
    uint16_t channel_6;
    uint16_t channel_7;
}tS_adc_raw_data;

typedef struct
{
    float channel_0;
    float channel_1;
    float channel_2;
    float channel_3;
    float channel_4;
    float channel_5;
    float channel_6;
    float channel_7;
}tS_procces_data;

typedef struct
{
    uint32_t convert_channel_0;
    uint32_t convert_channel_1;
    uint32_t convert_channel_2;
    uint32_t convert_channel_3;
    uint32_t convert_channel_4;
    uint32_t convert_channel_5;
    uint32_t convert_channel_6;
    uint32_t convert_channel_7;
    
    uint16_t convert_channel_0_f;
    uint16_t convert_channel_1_f;
    uint16_t convert_channel_2_f;
    uint16_t convert_channel_3_f;
    uint16_t convert_channel_4_f;
    uint16_t convert_channel_5_f;
    uint16_t convert_channel_6_f;
    uint16_t convert_channel_7_f;
}tS_convert_data;

typedef struct
{
    uint32_t pay;
    uint32_t payda;
    float ortalama;
}tS_driver_limit;

tS_adc_raw_data adc_raw_data;   // Raw data read from the relevant ADC channel.
tS_procces_data procces_data;   // Processed raw data read.
tS_convert_data convert_data;   // prossed data is scaled 0-999
tS_driver_limit driver_limit;
#ifdef	__cplusplus
}
#endif

#endif	/* FS_ADC_H */

