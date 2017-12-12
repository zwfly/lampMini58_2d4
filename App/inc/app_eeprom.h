/*
 * app_eeprom.h
 *
 *  Created on: 2017Äê9ÔÂ8ÈÕ
 *      Author: fly
 */

#ifndef APP_INC_APP_EEPROM_H_
#define APP_INC_APP_EEPROM_H_



void app_eeprom_Init(void);
void app_eeprom_get_dome_with_index(DOME_DEFAULT_T* dd, uint8_t index);

void app_eeprom_erase(uint32_t addr);
void app_eeprom_write_int(uint32_t addr, uint32_t d);
uint32_t app_eeprom_read_int(uint32_t addr);

#endif /* APP_INC_APP_EEPROM_H_ */
