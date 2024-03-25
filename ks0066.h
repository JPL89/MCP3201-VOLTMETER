// @File                KS0066.H	 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		Brazil
// @Date		11/10/22
//
//
// Copyright (C) 2021  JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//

#ifndef KS0066_H
#define KS0066_H

#include <xc.h>

#define RS PORTBbits.RB1
#define RW PORTBbits.RB2
#define EN PORTBbits.RB3
#define D4 PORTBbits.RB4
#define D5 PORTBbits.RB5
#define D6 PORTBbits.RB6
#define D7 PORTBbits.RB7

#define RS_TRIS TRISBbits.TRISB1    
#define RW_TRIS TRISBbits.TRISB2     
#define EN_TRIS TRISBbits.TRISB3      
#define D4_TRIS TRISBbits.TRISB4      
#define D5_TRIS TRISBbits.TRISB5     
#define D6_TRIS TRISBbits.TRISB6  
#define D7_TRIS TRISBbits.TRISB7

void KS0066_Command(unsigned char data);
void KS0066_Char(unsigned char data);
void KS0066_Goto(unsigned char x, unsigned char y);
void KS0066_String(const char *data);
void KS0066_Clear(unsigned char Line);
void KS0066_Custom(unsigned char loc, const unsigned char data[]);
void KS0066_Init(void);

#endif // KS0066_H