#include "bsp.h"

void bsp_Init(void) {

//	Wireless2d4_InitHard();
	Relay_InitHard();

	bsp_InitKey();

//	Timer1_InitHard();

//	InitialUART0_Timer1(115200);

//	Light_InitHard();
//	Timer0_InitHard();

	Uart_InitHard();

//	set_EA;         //enable interrupts

}

