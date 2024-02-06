/*
 * tool.c
 *
 *  Created on: 2024/02/07
 *      Author: sata
 */

#include "tool.h"

uint16 count_str(uint8 *buf) {
	uint16 i;
	uint8 tmp;

	for (i = 0; tmp != '\0'; i++) {
		if (0xFFFF == i) {
			i = 0;
			break;
		}
		buf++;
	}

	return i;
}

