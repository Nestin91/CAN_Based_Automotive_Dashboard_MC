/*
 * File:   rpm_indicator.c
 * Author: Nestin Gregorios Sunny
 * Description: CAN Based Automotive Dashboard
 *              Implement ECU2 [RPM and Indicator]
 * Created on 31 October, 2025, 4:37 PM
 */
#include <xc.h>

#include "digital_keypad.h"
#include "adc.h"
#include "main_ecu2.h"
#include "ssd.h"
#include "can.h"
#include "msg_id.h"

static unsigned char ssd[4] = {ZERO, ZERO, ZERO, ZERO};
static unsigned char digit[] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

unsigned int rpm;
unsigned int count;
unsigned int key = ALL_RELEASED;

unsigned char indicator[4][4] = {"OFF", "LS", "RS", "HL"};

void get_rpm()
{
    rpm = read_adc(CHANNEL4) * 5.866;
    ssd[0] = digit[(rpm / 1000) % 10];
    ssd[1] = digit[(rpm / 100) % 10];
    ssd[2] = digit[(rpm / 10) % 10];
    ssd[3] = digit[rpm % 10];
    
    SSD_Display(ssd);
    
    uint8_t rpm_data[5];
    rpm_data[0] = ((rpm / 1000) % 10) + '0';;
    rpm_data[1] = ((rpm / 100) % 10) + '0';
    rpm_data[2] = ((rpm / 10) % 10) + '0';
    rpm_data[3] = (rpm % 10) + '0';
    rpm_data[4] = '\0';
    can_transmit(RPM_MSG_ID, rpm_data, 5);
}

void get_indicator()
{
    static unsigned int index = 0;
    static unsigned int blink_flag = 0;
    key = read_digital_keypad(STATE_CHANGE);
    if (key == SWITCH1)     //left indicator
    {
        blink_flag = 1;     
        RB0 = RB1 = RB6 = RB7 = 0;
        index = 1;
    }
    else if (key == SWITCH2)    //right indicator
    {
        blink_flag = 2;       
        RB0 = RB1 = RB6 = RB7 = 0;
        index = 2;
    }
    else if (key == SWITCH3)    // hazard lamb
    {
        blink_flag = 3;
        RB0 = RB1 = RB6 = RB7 = 0;
        index = 3;
    }
    else if(key == SWITCH4)     // turnoff all LED which were turned on
    {
        blink_flag = 4;
        RB0 = RB1 = RB6 = RB7 = 0;
        index = 0;
    }
    
    if(blink_flag == 1)
    {
        if(count++ > 10)
        {
            RB0 = !RB0;
            RB1 = !RB1;
            count = 0;
        }
    }
    else if(blink_flag == 2)
    {
        if(count++ > 10)
        {
            RB6 = !RB6;
            RB7 = !RB7;
            count = 0;
        }
    }
    else if(blink_flag == 3)
    {
        if(count++ > 10)
        {
            RB0 = !RB0;
            RB1 = !RB1;
            RB6 = !RB6;
            RB7 = !RB7;
            count = 0;
        }
    }
    else if(blink_flag == 4)
    {
        if(count++ > 10)
        {
            RB0 = RB1 = RB6 = RB7 = 0;
            count = 0;
        }
    }
    can_transmit(INDICATOR_MSG_ID, indicator[index], 4);
}

