/*
 * File:   main.c
 * Author: Nestin Gregorios Sunny
 * Description: CAN Based Automotive Dashboard
 *              Implement ECU2 [RPM and Indicator]
 * Created on 31 October, 2025, 4:37 PM
 */


#include <xc.h>

#include "ssd.h"
#include "adc.h"
#include "digital_keypad.h"
#include "main_ecu2.h"
#include "can.h"
#include "msg_id.h"

/* delay 1ms function */
void delay(unsigned short factor)
{
	unsigned short i, j;

	for (i = 0; i < factor; i++)
	{
		for (j = 500; j--; );
	}
}

void init_config()
{
    TRISB = 0x00;
    PORTB = 0x00;
        
    TRISA = TRISA & 0xF0;
    TRISD = 0x00;
    
    init_can();
    init_adc();
    init_digital_keypad();
}

void main(void) 
{
    init_config();
    while(1)
    {
        get_rpm();
        delay(100);

        get_indicator();        
        delay(100);

    }
    return;
}
