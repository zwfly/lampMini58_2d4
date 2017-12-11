#include "bsp.h"

void bsp_Init(void) {

	Wireless2d4_InitHard();
	
	Relay_InitHard();

	bsp_InitKey();

	Light_InitHard();
	
		bsp_InitUart();
	
	Timer0_InitHard();

//	Uart_InitHard();

}

