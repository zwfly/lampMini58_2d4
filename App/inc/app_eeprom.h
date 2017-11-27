/*
 * app_eeprom.h
 *
 *  Created on: 2017Äê9ÔÂ8ÈÕ
 *      Author: fly
 */

#ifndef APP_INC_APP_EEPROM_H_
#define APP_INC_APP_EEPROM_H_

//#define DOME_START_ADDR   0x3C00  //use 3KB
//#define DOME_START_ADDR   0x3E00  //use 2.5KB
#define DOME_START_ADDR   0x6C00  //use 5KB

void app_eeprom_Init(void);
void app_eeprom_get_dome_with_index(DOME_DEFAULT_T* dd, uint8_t index);

void app_eeprom_erase(uint32_t addr);
void app_eeprom_write_int(uint32_t addr, uint32_t d);
uint32_t app_eeprom_read_int(uint32_t addr);
void app_eeprom_write_buf(uint16_t addr, uint8_t *pt, uint8_t len);

#endif /* APP_INC_APP_EEPROM_H_ */
