/*
 * File:   main.c
 * Author: Nestin Gregorios Sunny
 * Description: CAN Based Automotive Dashboard
 *              Implement ECU3 [Display Output in CLCD using CAN]
 * 
 * Sample Output:
 *                  SPD GE RPM  IND
 *                  99  G5 6000 OFF
 *                   
 * Created on 4 November, 2025, 10:25 PM
 */


#include <xc.h>

#include "can.h"
#include "message_handler.h"
#include "msg_id.h"
#include "clcd.h"


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
    
    init_clcd();
    init_can();
}

void main(void) 
{
    init_config();
    while(1)
    {        
        clcd_print("SPD GE RPM  IND", LINE1(0));
        process_canbus_data();
        delay(50);
    }
    return;
}
