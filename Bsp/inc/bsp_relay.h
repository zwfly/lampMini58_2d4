/*
 * bsp_relay.h
 *
 *  Created on: 2017Äê8ÔÂ18ÈÕ
 *      Author: fly
 */

#ifndef BSP_INC_BSP_RELAY_H_
#define BSP_INC_BSP_RELAY_H_

void Relay_InitHard(void);
void Relay_on(void);
void Relay_off(void);
void Relay_toggle(void);
uint8_t Relay_IsOn(void);
void Relay_set(uint8_t s);

#endif /* BSP_INC_BSP_RELAY_H_ */
