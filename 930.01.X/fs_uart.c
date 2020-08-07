#include "fs_uart.h"

//*****************************HABERLEŞME KESMESİ*****************************//
void __interrupt (low_priority) UART (void)
{
    if(PIE1bits.RC1IE && PIR1bits.RC1IF) //uart1 RX ucuna bilgi geldi mi?
    {
        if(RCSTA1bits.OERR)	//hata varmı
        {
            RCSTA1bits.CREN=0; // ALIMI DURDUR
            RCSTA1bits.CREN=1; // Veri alımına devam et.
        }
        read_byte = RCREG1; 
    }

    if (PIE3bits.RC2IE && PIR3bits.RC2IF) //uart2 rx ucuna bilgi geldi mi?
    {
           if(RCSTA2bits.OERR)	//hata varmı
        {
            RCSTA2bits.CREN=0; // ALIMI DURDUR
            RCSTA2bits.CREN=1; // Veri alımına devam et.
        }
        read_byte = RCREG2; 
    }
}
    

void usart1_init(void) 
{
//*Baudrate hesaplanıyor. 115200 için*//
    //BAUDCON1bits.BRG16 = 1;
    //SPBRG1 =34;
    BAUDCON1bits.BRG16 = 0;
    SPBRG1 = 103;
   
//***********************************//

    TX1STAbits.TXEN = 1; // Veri gönderimi etkinleştiriliyor.
    RC1STAbits.CREN = 1; // Haberleşme modu belirleniyor.
    RC1STAbits.SPEN = 1; // Seri port aktif etme biti etkinleştiriliyor.

    PIR1bits.TX1IF = 0;  // Veri gönderim yetkilentirme bayrağı. Başlangıçta boşaltılıyor.
    PIR1bits.RC1IF = 0;  // Veri alma yetkinlendirme bayrağı. Başlangıçta boşaltılıyor.
    PIE1bits.RC1IE = 1;  // RX kesmesinde izin verme biti.

    INTCONbits.PEIE = 1; // Bütün kesmelere izin verme biti.
    INTCONbits.GIE = 1;  // İzin verilen bütün kesmeler aktif ediliyor.

    RX1 = 1; //RX pin set as input
    TX1 = 0; //TX pin set as output
}


/**
  * @brief 		The function that transmit one byte.
  *
  * @return 	bool transmit_in_progress
  */
uint8_t transmit(void)
{
	uint8_t transmit_in_progress = 0;

	if( ( transmit_tail & UART_BUFFER_SIZE_MASK ) != ( transmit_head & UART_BUFFER_SIZE_MASK ) )
	{
		TX2REG = transmit_buffer[ (transmit_tail++) & UART_BUFFER_SIZE_MASK ];
		transmit_in_progress = 1;
	}
	else
	{
		transmit_in_progress = 0;
	}

	return transmit_in_progress;
}


void usart2_init(void) 
{
//*baudrate hesaplanıyor. 96000 için*//
    BAUDCON2bits.BRG16 = 0;
    SPBRG2 = 103;
//***********************************//
    TX2STAbits.TXEN = 1;
    RC2STAbits.CREN = 1;
    RC2STAbits.SPEN = 1;

    PIR3bits.TX2IF = 0;
    PIR3bits.RC2IF = 0;
    PIE3bits.RC2IE = 1;

    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;

    RX2 = 1; //RX pin set as input
    TX2 = 0; //TX pin set as output
}

