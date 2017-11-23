/*
 * bsp_uart.h
 *
 *  Created on: 2017Äê6ÔÂ27ÈÕ
 *      Author: fly
 */

#ifndef BSP_INC_BSP_UART_H_
#define BSP_INC_BSP_UART_H_

#define RCV_BUFSIZE  160

typedef struct _RCV_T {

	uint8_t rxBuf[RCV_BUFSIZE];
	uint8_t pWrite;
	uint8_t pRead;

} RCV_T;

extern RCV_T rcv_T;
extern uint8_t riflag;

void Uart_InitHard(void);

#endif /* BSP_INC_BSP_UART_H_ */
