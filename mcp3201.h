// @File		MCP3201.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		23/03/24
//
//
// Copyright (C) 2024 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#ifndef MCP3201_H
#define MCP3201_H

#define MCP3201_SCK PORTAbits.RA0
#define MCP3201_SDO PORTAbits.RA1
#define MCP3201_CS PORTAbits.RA2

#define MCP3201_SCK_TRIS TRISAbits.TRISA0
#define MCP3201_SDO_TRIS TRISAbits.TRISA1
#define MCP3201_CS_TRIS TRISAbits.TRISA2

unsigned char SPI_read(void)
{
    unsigned char data = 0;
    
    for(unsigned char mask = 0x80; mask; mask >>=1)
    {
        data <<= 1;
        if(MCP3201_SDO) data |= 1;
        
        MCP3201_SCK = 1;
        __asm__ __volatile__("nop");
        MCP3201_SCK = 0;        
        __asm__ __volatile__("nop");
    }
    
    return ((unsigned char) data);
}

unsigned short MCP3201_read(void)
{
    unsigned char msb  = 0;
    unsigned char lsb  = 0;
    
    MCP3201_CS = 0;
    msb = SPI_read();
    lsb = SPI_read();
    MCP3201_CS = 1;
    
    unsigned short data = (unsigned short) (((msb << 8) | lsb));    
    data = (unsigned short) (data >> 1);    
    return ( (unsigned short) (data));
}

void MCP3201_init(void)
{
    MCP3201_SCK_TRIS = 0;
    MCP3201_SDO_TRIS = 1;
    MCP3201_CS_TRIS = 0;
    
    MCP3201_CS = 1;
}

#endif
