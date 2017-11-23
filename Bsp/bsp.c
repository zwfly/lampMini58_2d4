#include "bsp.h"

BIT BIT_TMP;  //WTF

void bsp_Init(void) {

//	clr_BODEN;


//	Set_All_GPIO_Quasi_Mode();
//	Set_All_GPIO_Input_Mode();

	Wireless2d4_InitHard();
	Relay_InitHard();

	bsp_InitKey();

//	Timer1_InitHard();

//	InitialUART0_Timer1(115200);

	Light_InitHard();
	Timer0_InitHard();


	Uart_InitHard();

	set_EA;         //enable interrupts

}

