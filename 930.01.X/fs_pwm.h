/* 
 * File:   fs_pwm.h
 * Author: Faruk Sozuer
 *
 * Created on July 16, 2020, 7:29 PM
 */

#ifndef FS_PWM_H
#define	FS_PWM_H

#ifdef	__cplusplus
extern "C" {
#endif


#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void PWM_Init(void);    
void PWM1_setDC(int16_t dutycycle);
void PWM2_setDC(int16_t dutycycle);

#ifdef	__cplusplus
}
#endif

#endif	/* FS_PWM_H */

