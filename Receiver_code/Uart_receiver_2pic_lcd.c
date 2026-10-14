#include <xc.h>
#define _XTAL_FREQ 16000000
#include "lcd_4_uart.h"
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define RS PORTBbits.RB0
#define EN PORTBbits.RB1

void UART_Init()
{
    SPBRG = 103;
    SYNC = 0;
    SPEN = 1;
    TX9 = 0;
    RX9 = 0;
    BRGH = 1;
    TXEN = 1;
    CREN = 1;
}

void UART_Write(char data)
{
    while(!TRMT);
     TXREG = data;   
}

void UART_Write_Text(const char *text)
{
    while(*text)
    {
        UART_Write(*text++);
    }
}

char UART_Read()
{
    while(!RCIF);
    return RCREG;
}
void main()
{
    char data;
    
     TRISB = 0x00;
    PORTB = 0x00;
    TRISD = 0;
    PORTD = 0;
    
    UART_Init();
    lcd_init();
    
    while(1)
    {
        data = UART_Read();
        lcd_data(data);
    }
}