/* 
 * File:   main_ecu1.h
 * Author: Nestin Gregorios Sunny
 * Description: CAN Based Automotive Dashboard
 *              Implement ECU1 [Speed and Gear]
 * Created on 29 October, 2025, 8:51 AM
 */

#ifndef MAIN_ECU1_H
#define	MAIN_ECU1_H

#include <stdint.h>
#include "digital_keypad.h"
#include <xc.h>

#define MAX_GEAR 6
#define SPEED_ADC_CHANNEL 0x04
#define GEAR_UP             MK_SW1
#define GEAR_DOWN           MK_SW2
#define COLLISION           MK_SW3

void get_speed();
void get_gear_pos();

#endif	/* MAIN_ECU1_H */

