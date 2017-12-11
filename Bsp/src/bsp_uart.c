/*
 * bsp_uart.c
 *
 *  Created on: 2017Äê6ÔÂ27ÈÕ
 *      Author: fly
 */
#include <string.h>
#include "bsp.h"
#include <stdint.h>

//RCV_T rcv_T;

void Uart_InitHard(void) {

	/* Enable IP clock */
	CLK_EnableModuleClock(UART0_MODULE);

	/* Select IP clock source */
	CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UARTSEL_HIRC,
			CLK_CLKDIV_UART(1));

	/*---------------------------------------------------------------------------------------------------------*/
	/* Init I/O Multi-function                                                                                 */
	/*---------------------------------------------------------------------------------------------------------*/
	/* Set P1 multi-function pins for UART RXD, TXD */
	SYS->P5_MFP = SYS_MFP_P51_UART0_RXD | SYS_MFP_P50_UART0_TXD;

	/* Reset IP */
	SYS_ResetModule(SYS_IPRST1_UART0RST_Msk);

	/* Configure UART and set UART Baudrate */
	UART_Open(UART0, 115200);

///////////
	/* Init UART1 */

	/* Enable IP clock */
	CLK_EnableModuleClock(UART1_MODULE);

	/* Select IP clock source */
	CLK_SetModuleClock(UART1_MODULE, CLK_CLKSEL1_UARTSEL_HIRC,
			CLK_CLKDIV_UART(1));

	/*---------------------------------------------------------------------------------------------------------*/
	/* Init I/O Multi-function                                                                                 */
	/*---------------------------------------------------------------------------------------------------------*/
	/* Set P1 multi-function pins for UART RXD, TXD */
	SYS->P2_MFP = SYS_MFP_P24_UART1_RXD | SYS_MFP_P25_UART1_TXD;

	/* Reset IP */
	SYS_ResetModule(SYS_IPRST1_UART1RST_Msk);

	/* Configure UART and set UART Baudrate */
	UART_Open(UART1, 19200);

    /* Enable Interrupt and install the call back function */
    UART_ENABLE_INT(UART1, (UART_INTEN_RDAIEN_Msk | UART_INTEN_THREIEN_Msk | UART_INTEN_RXTOIEN_Msk));
    NVIC_EnableIRQ(UART1_IRQn);
}

/*---------------------------------------------------------------------------------------------------------*/
/* ISR to handle UART Channel 0 interrupt event                                                            */
/*---------------------------------------------------------------------------------------------------------*/
void UART1_IRQHandler(void) {

	uint8_t u8InChar = 0xFF;
	uint32_t u32IntSts = UART1->INTSTS;

	if (u32IntSts & UART_INTSTS_RDAINT_Msk) {

		/* Get all the input characters */
		while (UART_IS_RX_READY(UART1)) {
			/* Get the character from UART Buffer */
			u8InChar = UART_READ(UART1); /* Rx trigger level is 1 byte*/

		}
	}

	if (u32IntSts & UART_INTSTS_THREINT_Msk) {


			UART_WRITE(UART1, u8InChar);

		
	}

}

