/*
 * GPIO.c
 *
 *  Created on: 2024/02/05
 *      Author: sata
 */

#include "GPIO.h"



void led_stop(void) {
	// 全部OFF
	PORTC.PODR.BIT.B0 = 0;	// LED1
	PORTC.PODR.BIT.B1 = 0;	// LED2
	PORT0.PODR.BIT.B2 = 0;	// LED3
	PORT0.PODR.BIT.B3 = 0;	// LED4
}

void led_on(LED_NUM num) {
	switch (num)
	{
	case LED1:
		PORTC.PODR.BIT.B0 = 1;
		break;
	case LED2:
		PORTC.PODR.BIT.B1 = 1;
		break;
	case LED3:
		PORT0.PODR.BIT.B2 = 1;
		break;
	case LED4:
		PORT0.PODR.BIT.B3 = 1;
		break;
	default:
		break;
	}
}

void led_off(LED_NUM num) {
	switch (num)
	{
	case LED1:
		PORTC.PODR.BIT.B0 = 0;
		break;
	case LED2:
		PORTC.PODR.BIT.B1 = 0;
		break;
	case LED3:
		PORT0.PODR.BIT.B2 = 0;
		break;
	case LED4:
		PORT0.PODR.BIT.B3 = 0;
		break;
	default:
		break;
	}
}
