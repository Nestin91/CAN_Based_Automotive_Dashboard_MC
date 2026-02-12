/*
 * File:   main.c
 * Author: Nestin Gregorios Sunny
 * Description: CAN Based Automotive Dashboard
 *              Implement ECU1 [Speed and Gear]
 * Created on 29 October, 2025, 7:25 AM
 */


#include <xc.h>

#include "main_ecu1.h"
#include "adc.h"
#include "ssd.h"
#include "can.h"
#include "digital_keypad.h"
#include "msg_id.h"

//#include "mkp.h"
//#include "clcd.h"


unsigned char event[9][3] = {"ON", "GN", "G1", "G2", "G3", "G4", "G5", "GR", "_C"};

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
    TRISA = TRISA & 0xF0;
    TRISD = 0x00;
    
    init_digital_keypad();
    init_adc();
    init_can();
    //init_matrix_keypad();
    //init_clcd();
}

void main(void) 
{   
    init_config();
    while(1)
    {
        // Get speed and prepare CAN payload
        get_speed();
        delay(100);
        // Get gear and prepare CAN payload
        get_gear_pos();
        delay(100);
    }
    return;
}
