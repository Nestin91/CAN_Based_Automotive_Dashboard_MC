#include <xc.h>
#include "ssd.h"


void SSD_Display(unsigned char Data[])
{
    volatile unsigned int i, wait;
    for(i = 0; i < 4; i++)
    {
        PORTD = Data[i];
        PORTA = (PORTA & 0xF0) | (1 << i);
        for(wait = 3000; wait--;);
    }
}



