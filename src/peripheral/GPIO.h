/*
 * GPIO.h
 *
 *  Created on: 2024/02/05
 *      Author: sata
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "common.h"

typedef enum {
	LED1,
	LED2,
	LED3,
	LED4
} LED_NUM;


void led_stop(void);
void led_on(LED_NUM num);
void led_off(LED_NUM num);


#endif /* GPIO_H_ */
