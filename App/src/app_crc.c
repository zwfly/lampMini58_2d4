/*
 * app_crc.c
 *
 *  Created on: 2017Äê8ÔÂ31ÈÕ
 *      Author: fly
 */
#include "app.h"

static uint8_t crc;
static uint8_t i;

uint8_t app_CalcCRC8(uint8_t *ptr, uint8_t len) {

	crc = 0;
	while (len--) {
		crc ^= *ptr++;
		for (i = 0; i < 8; i++) {
			if (crc & 0x01)
				crc = (crc >> 1) ^ 0x8C;
			else
				crc >>= 1;
		}
	}
	return crc;
}

uint8_t app_CalcCRC8_cycle(uint8_t *ptr, uint16_t len, uint16_t pos,
		uint16_t bufLen) {
	crc = 0;
	while (len--) {
		crc ^= *ptr++;
		pos++;
		if (pos >= bufLen) {
			pos = 0;
			ptr -= bufLen;
		}
		for (i = 0; i < 8; i++) {
			if (crc & 0x01)
				crc = (crc >> 1) ^ 0x8C;
			else
				crc >>= 1;
		}
	}
	return crc;
}
