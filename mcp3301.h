// @File		MCP3301.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		Brazil
// @Date		07/04/23
//
//
// Copyright (C) 2023  JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#ifndef MCP3301_H
#define MCP3301_H

#define MCP3301_SCK PORTAbits.RA0
#define MCP3301_SDO PORTAbits.RA1
#define MCP3301_CS PORTAbits.RA2

#define MCP3301_SCK_TRIS TRISAbits.TRISA0
#define MCP3301_SDO_TRIS TRISAbits.TRISA1
#define MCP3301_CS_TRIS TRISAbits.TRISA2

unsigned char SPI_read(void)
{
    unsigned char data = 0;
    
    for(unsigned char mask = 0x80; mask; mask >>=1)
    {
        data <<= 1;
        if(MCP3301_SDO) data |= 1;
        
        MCP3301_SCK = 1;
        __asm__ __volatile__("nop");
        MCP3301_SCK = 0;        
        __asm__ __volatile__("nop");
    }
    
    return ((unsigned char) data);
}

// BYTE CHANNEL 
// MSB FIRST: START, DIFF, D2, D1, D0, 0, 0, 0
unsigned short MCP3301_Read(unsigned char ch)
{                     
    unsigned char msb = 0;
    unsigned char lsb = 0;  
    
    MCP3301_CS = 0;    
    msb = SPI_read();
    lsb = SPI_read();    
    MCP3301_CS = 1;    
    
    unsigned short data = (unsigned short) (((msb << 8) | lsb));    
    data = (unsigned short) (data & 0x0FFF);    
    return ( (unsigned short) (data));
}

void MCP3301_Init(void)
{
    MCP3301_SCK_TRIS = 0;
    MCP3301_SDO_TRIS = 1;
    MCP3301_CS_TRIS = 0;
    
    MCP3301_CS = 1;
}

#endif 
