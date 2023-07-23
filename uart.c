#include "uart.h"

void UART_Init(const unsigned long baudRate) {
    unsigned long x;
    x = _XTAL_FREQ/(64*(baudRate+1));
    if(x > 255) {
        x = _XTAL_FREQ/(16*(baudRate+1));
        TXSTAbits.BRGH = 1;   // High Baud Rate Select bit | Asynchronous mode
    }
    if(x <= 255) SPBRG = (char)x; // EUSART Baud Rate Generator Register Low Byte
    
    TRISCbits.RC6   = 1;// TX
    TRISCbits.RC7   = 1;// RX
    INTCONbits.GIE  = 1;// Global Interrupt Enable Bit
    INTCONbits.PEIE = 1;// Peripherals Interrupt Enable Bit
    // PIE1bits.RCIE   = 1;// ESUART Receving Interrupt Enable Bit
    RCSTAbits.SPEN  = 1;// Serial Port Enable bit
    RCSTAbits.CREN  = 1;// Enable Data Continous Reception
    TXSTAbits.SYNC  = 0;// Enable Asynchronous mode
    TXSTAbits.TXEN  = 1;// Enable UART Transmission
}

unsigned char UART_Rx_Ready(void) {
    if(PIR1bits.RCIF == 1) return 1;
    else return 0;
}

char UART_Read(void) {
    while(PIR1bits.RCIF == 0);
    return RCREG;
}

void UART_Read_String(char *str, char len) {
    for(int i = 0; i < len; i++) str[i] = UART_Read();
}

unsigned char UART_Tx_Ready(void) {
    if(PIR1bits.TXIF == 1) return 1;
    else return 0;
}

void UART_Write(char chr) {
    TXREG = chr;
    while(PIR1bits.TXIF == 0);
}

void UART_Write_String(char *str) {
    for(int i = 0; str[i] != '\0'; i++) UART_Write(str[i]);
}
