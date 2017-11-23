/*
 * bsp_relay.c
 *
 *  Created on: 2017Äê8ÔÂ18ÈÕ
 *      Author: fly
 */
#include "bsp.h"

void Relay_InitHard(void) {

	clr_P1M1_4;
	P1M2 |= SET_BIT4;

	Relay_off();
}
void Relay_on(void) {
	P14 = 1;
}
void Relay_off(void) {
	P14 = 0;
}
void Relay_toggle(void) {
	P14 = ~P14;
}
uint8_t Relay_IsOn(void) {
	return P14;
}
void Relay_set(uint8_t s) {
	if (s) {
		Relay_on();
	} else {
		Relay_off();
	}
}
