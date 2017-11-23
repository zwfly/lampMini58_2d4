/*
 * app_crc.h
 *
 *  Created on: 2017Äê8ÔÂ31ÈÕ
 *      Author: fly
 */

#ifndef APP_INC_APP_CRC_H_
#define APP_INC_APP_CRC_H_

uint8_t app_CalcCRC8(uint8_t *ptr, uint8_t len);
uint8_t app_CalcCRC8_cycle(uint8_t *ptr, uint8_t len, uint8_t pos,
		uint8_t bufLen);

#endif /* APP_INC_APP_CRC_H_ */
