// PIC16F628A Configuration Bit Settings
// CONFIG
#pragma config FOSC = HS        
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config MCLRE = ON       
#pragma config BOREN = OFF      
#pragma config LVP = OFF        
#pragma config CPD = OFF        
#pragma config CP = OFF         

#define _XTAL_FREQ 16000000

#include <xc.h>
#include "ks0066.h"
#include "mcp3201.h"

int main(void) 
{    
    __delay_ms(500);
    
    // CLEAR PORTS
    PORTA = 0x00;
    PORTB = 0x00;
    
    // TURN OFF COMPARATOR
    // TO USE PORTA AS I/O 
    CMCON = 0x07;

    KS0066_Init();
    
    MCP3201_init();
    
    while(1)
    {
        unsigned short a = MCP3201_read();
        unsigned short b = a;
        
        double e = (double) ((b * 0.00122) / 5) *55;
        
        e = (double) (e * 100);
        
        b = (unsigned short)e;
        
        KS0066_Clear(0);
        KS0066_Clear(1);  
        
        KS0066_Goto(0,0);
        KS0066_String("ADC");

        KS0066_Goto(0,1);
        KS0066_String("VOLT");
        
        KS0066_Goto(6,0);
        KS0066_Char(48 + a / 1000 % 10);
        KS0066_Char(48 + a / 100 % 10);
        KS0066_Char(48 + a / 10 % 10);
        KS0066_Char(48 + a / 1 % 10);
        
        KS0066_Goto(6,1);
        KS0066_Char(48 + b / 1000 % 10);
        KS0066_Char(48 + b / 100 % 10);
        KS0066_Char(46);
        KS0066_Char(48 + b / 10 % 10);
        
        __delay_ms(500);
    }
    
    return 0;
}