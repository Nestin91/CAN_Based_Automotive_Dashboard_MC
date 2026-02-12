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
//#include "clcd.h"
//#include "mkp.h"
#include "digital_keypad.h"
#include "msg_id.h"
#include "can.h"
#include "ssd.h"

static unsigned char ssd[4] = {ZERO, ZERO, ZERO, ZERO};
static unsigned char digit[] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

unsigned int speed;
unsigned char event[9][3] = {"ON", "GN", "G1", "G2", "G3", "G4", "G5", "GR", "_C"};
unsigned int key = ALL_RELEASED;

void get_speed()
{
    speed = read_adc(CHANNEL4)/ 10.33;
#if 0
    clcd_print("SPEED:", LINE1(0));
    clcd_putch(((speed / 10) % 10) + 48, LINE2(0));
    clcd_putch((speed % 10) + 48, LINE2(1));
#else
    ssd[2] = digit[(speed / 10) % 10];
    ssd[3] = digit[speed % 10];
    
    SSD_Display(ssd);
    uint8_t speed_data[3];
    speed_data[0] = ((speed / 10) % 10) + '0';
    speed_data[1] = (speed % 10) + '0';
    speed_data[2] = '\0';

    can_transmit(SPEED_MSG_ID, speed_data, 3);
#endif
}

void get_gear_pos()
{
#if 0
    key = read_switches(STATE_CHANGE);

    static unsigned int index = 0, flag = 0;
   
    if(flag == 0)
    {
        if(key == MK_SW1)
        {
            // increment gear
            if(index < 7)
            {
                index++;
            }
        }
        else if(key == MK_SW2)
        {
            // decrement gear
            if(index > 1)
            {
                index--;
            }
        }
        else if(key == MK_SW3)
        {
            // collision "C"
            index = 8;
            flag = 1;
        }
    }
    else if(flag)
    {
        // After collision gear should go to neutral
        if(key == MK_SW1)
        {
            index = 1;
            flag = 0;
        }
    }
    clcd_print("GEAR:", LINE1(8));
    clcd_print(event[index], LINE2(8));
#else
    static unsigned int index = 0;
    static unsigned char flag = 0;

    key = read_digital_keypad(STATE_CHANGE);

    if (flag == 0)
    {
        if (key == SWITCH1 && index < 7)
        {
            index++;  // Increment gear
        }
        else if (key == SWITCH2 && index > 1)
        {
            index--;  // Decrement gear
        }
        else if (key == SWITCH3)
        {
            index = 8;  // Collision
            flag = 1;
        }
    }
    else
    {
        if (key == SWITCH1)
        {
            index = 1;  // Reset to Neutral after collision
            flag = 0;
        }
    }

    can_transmit(GEAR_MSG_ID, event[index], 3);
#endif
}
    