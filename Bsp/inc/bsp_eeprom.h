/*
 * bsp_eeprom.h
 *
 *  Created on: 2017Äê9ÔÂ8ÈÕ
 *      Author: fly
 */

#ifndef BSP_INC_BSP_EEPROM_H_
#define BSP_INC_BSP_EEPROM_H_

void EEPROM_InitHard(void);

void bsp_eeprom_write_byte(uint32_t u32addr, uint32_t u32data);
int32_t bsp_eeprom_erase(uint32_t u32addr);
uint32_t bsp_eeprom_read_byte(uint32_t u32Addr);

#endif /* BSP_INC_BSP_EEPROM_H_ */
