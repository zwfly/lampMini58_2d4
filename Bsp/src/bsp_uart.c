/*
 * bsp_uart.c
 *
 *  Created on: 2017Äê6ÔÂ27ÈÕ
 *      Author: fly
 */

#include "bsp.h"
#include <string.h>

 RCV_T rcv_T;

uint8_t riflag = 0;

void Uart_InitHard(void) {
	riflag = 0;

	memset((uint8_t *) &rcv_T, 0, sizeof(RCV_T));

//	InitialUART0_Timer1(115200);
	InitialUART0_Timer3(19200);
}

void SerialPort0_ISR(void)
interrupt 4
{
	if (RI == 1) { /* if reception occur */
		clr_RI; /* clear reception flag for next reception */
		rcv_T.rxBuf[rcv_T.pWrite++] = SBUF;
		if (rcv_T.pWrite >= RCV_BUFSIZE) {
			rcv_T.pWrite = 0;
		}
		riflag++;
	}
	if (TI == 1) {
		clr_TI; /* if emission occur */
	}
}

