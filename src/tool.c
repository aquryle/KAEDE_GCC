/*
 * tool.c
 *
 *  Created on: 2024/02/07
 *      Author: sata
 */

/**
 * @file tool.c
 * @author sata
 * @brief MCU independent functions
 * @version 0.1
 * @date 2024-02-07
 * @copyright Copyright (c) 2024
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

