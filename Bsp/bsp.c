#include "bsp.h"

void bsp_Init(void) {

	bsp_InitUart();

	EEPROM_InitHard();

	Wireless2d4_InitHard();

	Relay_InitHard();

	bsp_InitKey();

	Light_InitHard();

	Timer0_InitHard();

}

