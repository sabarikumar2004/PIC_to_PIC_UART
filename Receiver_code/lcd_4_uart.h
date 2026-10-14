#include <xc.h>

#define _XTAL_FREQ 16000000

#define RS PORTBbits.RB0
#define EN PORTBbits.RB1



void lcd_enable()
{
    EN =1;
    __delay_ms(2);
    EN = 0;
}
void lcd_cmd(unsigned char cmd)
{
    RS =0;
    PORTB =(PORTB & 0X03)|(cmd & 0XF0);
    lcd_enable();
    PORTB = (PORTB & 0x03)|((cmd<<4) & 0XF0);
    lcd_enable();
}
void lcd_data(unsigned char data)
{
    RS=1;
    PORTB =(PORTB & 0x03)|(data & 0XF0);
    lcd_enable();
    PORTB = (PORTB & 0x03)|((data<<4) &0XF0);
    lcd_enable();
}
void lcd_string(const char *str)
{
    while(*str)
    {
        lcd_data(*str++);
    }
}
void lcd_init()
{ 
    __delay_ms(20);
    lcd_cmd(0x02);
    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
    __delay_ms(2);
}