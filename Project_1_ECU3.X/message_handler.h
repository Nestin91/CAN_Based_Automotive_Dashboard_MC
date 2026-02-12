/* 
 * File:   message_handler.h
 * Author: Nestin Gregorios Sunny
 * Description: CAN Based Automotive Dashboard
 *              Implement ECU3 [Display Output in CLCD using CAN]
 * 
 * Sample Output:
 *                  SPD GE RPM  IND
 *                  99  G5 6000 OFF
 *
 * Created on 5 November, 2025, 7:38 AM
 */

#ifndef MESSAGE_HANDLER_H
#define	MESSAGE_HANDLER_H

#include <stdint.h>

#define LED_OFF 0
#define LED_ON 1

#define RIGHT_IND_ON() (PORTB = PORTB | 0xC0)
#define RIGHT_IND_OFF() (PORTB = PORTB & ~0xC0)
#define LEFT_IND_ON() (PORTB = PORTB | 0x03)
#define LEFT_IND_OFF() (PORTB = PORTB & ~0x03)

extern volatile unsigned char led_state, status;

typedef enum {
    e_ind_off,
    e_ind_left,
    e_ind_right,
    e_ind_hazard
} IndicatorStatus;

void process_canbus_data();
void handle_speed_data(uint8_t *data, uint8_t len);
void handle_gear_data(uint8_t *data, uint8_t len);
void handle_rpm_data(uint8_t *data, uint8_t len);
void handle_indicator_data(uint8_t *data, uint8_t len);


#endif	/* MESSAGE_HANDLER_H */

