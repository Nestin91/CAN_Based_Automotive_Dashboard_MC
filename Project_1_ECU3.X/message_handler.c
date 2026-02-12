/*
 * File:   message_handler.c
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
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"

unsigned char event[9][3] = {"ON", "GN", "G1", "G2", "G3", "G4", "G5", "GR", "_C"};
unsigned char indicator[4][4] = {"OFF", "L_S", "R_S", "H_L"};
unsigned int count;

volatile unsigned char led_state = LED_OFF, status = e_ind_off;


void handle_speed_data(uint8_t *data, uint8_t len)
{
    //Implement the speed function
    //clcd_print("SPD", LINE1(0));
    clcd_print(data, LINE2(0));
}

void handle_gear_data(uint8_t *data, uint8_t len) 
{
    //Implement the gear function
    //clcd_print("GE", LINE1(5));
    clcd_print(data, LINE2(4));
}

void handle_rpm_data(uint8_t *data, uint8_t len) 
{
    //Implement the rpm function
    //clcd_print("RPM", LINE1(8));
    clcd_print(data, LINE2(7));
}

void handle_indicator_data(uint8_t *data, uint8_t len) 
{
    //Implement the indicator function
    //clcd_print("IND", LINE1(13));
    
    clcd_print(data, LINE2(12));
    if (strcmp((char *)data, indicator[0]) == 0)
    {
        // OFF
        if(count++ > 10)
        {
            RB0 = RB1 = RB6 = RB7 = 0;
            count = 0;
        }
    }
    else if (strcmp((char *)data, indicator[1]) == 0)
    {
        // Left Indicator
        if(count++ > 10)
        {
            RB0 = !RB0;
            RB1 = !RB1;
            count = 0;
        }
    }
    else if (strcmp((char *)data, indicator[2]) == 0)
    {
        // Right Indicator
        if(count++ > 10)
        {
            RB6 = !RB6;
            RB7 = !RB7;
            count = 0;
        }
    }
    else if (strcmp((char *)data, indicator[3]) == 0)
    {
        // Hazard lamp
        if(count++ > 10)
        {
            RB0 = !RB0;
            RB1 = !RB1;
            RB6 = !RB6;
            RB7 = !RB7;
            count = 0;
        }
    }
}

void process_canbus_data() 
{   
    uint16_t id;
    uint8_t data[8];
    uint8_t len = 0;
    //process the CAN bus data
    can_receive(&id, data, &len);
    if(id == SPEED_MSG_ID)
    {
        handle_speed_data(data, len);
    }
    else if(id == GEAR_MSG_ID)
    {
        handle_gear_data(data, len);
    }
    else if(id == RPM_MSG_ID)
    {
        handle_rpm_data(data, len);
    }
    else if(id == INDICATOR_MSG_ID)
    {
        handle_indicator_data(data, len);
    }
}
