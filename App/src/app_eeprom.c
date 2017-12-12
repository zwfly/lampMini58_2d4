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
	uint8_t availableGroup = 0;
	uint8_t minSpaceBytes = 0;
	if (sizeof(DOME_DEFAULT_T) % 4) {
		minSpaceBytes = (sizeof(DOME_DEFAULT_T) / 4) * 4 + 4;
	} else {
		minSpaceBytes = sizeof(DOME_DEFAULT_T);
	}
	availableGroup = (FMC_APROM_END - DOME_START_ADDR) / minSpaceBytes;

	if (index >= availableGroup) {
		index = 0;
	}
	uint16_t i = 0;
	uint8_t *pt = (uint8_t *) dd;
	SYS_UnlockReg();
	FMC_Open();
	for (i = 0; i < (sizeof(DOME_DEFAULT_T) / 4); i++) {
		uint8_t j = 0;
		uint32_t dt = app_eeprom_read_int(index * minSpaceBytes + i * 4);
		for (j = 0; j < 4; j++) {
			*(pt + i * 4 + j) = (dt >> (j * 8)) & 0xFF;
		}
	}
	if (sizeof(DOME_DEFAULT_T) % 4) {
		uint32_t dt = app_eeprom_read_int(
				index * minSpaceBytes + (sizeof(DOME_DEFAULT_T) / 4) * 4);
		for (i = 0; i < (sizeof(DOME_DEFAULT_T) % 4); i++) {
			*(pt + (sizeof(DOME_DEFAULT_T) / 4) * 4 + i) = (dt >> (i * 8))
					& 0xFF;
		}
	}
	FMC_Close();
	SYS_LockReg();
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

