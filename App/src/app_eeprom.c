/*
 * app_eeprom.c
 *
 *  Created on: 2017Äê9ÔÂ8ÈÕ
 *      Author: fly
 */
#include "app.h"
#include <string.h>

void app_eeprom_Init(void) {

}

void app_eeprom_get_dome_with_index(DOME_DEFAULT_T *dd, uint8_t index) {

	if (index >= ((FMC_APROM_END - DOME_START_ADDR) / sizeof(DOME_DEFAULT_T))) {
		index = 0;
	}
	uint8_t i = 0;
	uint8_t *pt = (uint8_t *) dd;
	uint8_t n = sizeof(DOME_DEFAULT_T);
	uint8_t minSpaceBytes = n;
	if (minSpaceBytes % 4) {
		minSpaceBytes++;
	}

	for (i = 0; i < (n / 4); i++) {
		uint8_t j = 0;
		uint32_t dt = app_eeprom_read_int(index * minSpaceBytes + i * 4);

		for (j = 0; j < 4; j++) {
			*(pt + i * 4 + j) = (dt >> (i * 8)) & 0xFF;
		}
	}
	for (i = 0; i < (n % 4); i++) {
	//	*(pt + (n / 4) * 4 + i + 1) = (dt >> (i * 8)) & 0xFF;
	}

}

void app_eeprom_save_dome_with_byte(DOME_DEFAULT_T *dd, uint8_t index) {

}

void app_eeprom_erase(uint32_t addr) {
	bsp_eeprom_erase(DOME_START_ADDR + addr);
}
void app_eeprom_write_int(uint32_t addr, uint32_t d) {
	bsp_eeprom_write_int(DOME_START_ADDR + addr, d);
}
uint32_t app_eeprom_read_int(uint32_t addr) {
	return bsp_eeprom_read_int(DOME_START_ADDR + addr);
}
void app_eeprom_write_buf(uint16_t addr, uint8_t *pt, uint8_t len) {
//write_DATAFLASH_BUF(DOME_START_ADDR + addr, pt, len);

}
void app_eeprom_100ms_pro(void) {

}

static void app_eeprom_pro(void) {

}
