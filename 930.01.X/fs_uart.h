/* 
 * File:   fs_uart.h
 * Author: Faruk Sozuer
 *
 * Created on July 18, 2020, 12:42 AM
 */

#ifndef FS_UART_H
#define	FS_UART_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define UART_BUFFER_SIZE            1024
const uint16_t UART_BUFFER_SIZE_MASK = UART_BUFFER_SIZE-1;
    
uint8_t  transmit_buffer[UART_BUFFER_SIZE] = {0};
uint16_t transmit_head 		  			   =  0;
uint16_t transmit_tail 		   			   =  0;
    
uint8_t read_byte;
uint8_t read_byte2;
    
void usart1_init(void);
void usart2_init(void);

void UART1_SendString(uint8_t *data);
void UART1_SendData(uint8_t data);
void UART2_SendData(uint8_t data);

uint8_t transmit(void);

#ifdef	__cplusplus
}
#endif

#endif	/* FS_UART_H */

