/*
 * bsp_relay.c
 *
 *  Created on: 2017Äê8ÔÂ18ÈÕ
 *      Author: fly
 */
#include "bsp.h"

void Relay_InitHard(void) {
	Relay_off();
	GPIO_SetMode(P1, BIT0, GPIO_MODE_OUTPUT);

}
void Relay_on(void) {
	P10 = 1;
}
void Relay_off(void) {
	P10 = 0;
}
void Relay_toggle(void) {
	P10 = ~P10;
}
uint8_t Relay_IsOn(void) {
	return P10;
}
void Relay_set(uint8_t s) {
	if (s) {
		Relay_on();
	} else {
		Relay_off();
	}
}
