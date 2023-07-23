#ifndef UART_H
#define	UART_H

#include <xc.h>

#define _XTAL_FREQ 20000000

void UART_Init(const unsigned long baudRate);
unsigned char UART_Rx_Ready(void);
char UART_Read(void);
void UART_Read_String(char *str, char len);
unsigned char UART_Tx_Ready(void);
void UART_Write(char chr);
void UART_Write_String(char* str);

#endif
