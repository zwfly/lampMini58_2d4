/*
 * app_uart.h
 *
 *  Created on: 2017Äê8ÔÂ31ÈÕ
 *      Author: fly
 */

#ifndef APP_INC_APP_UART_H_
#define APP_INC_APP_UART_H_

#define BT_MODE     0x01
#define FM_MODE     0x02
#define USB_MODE    0x03
#define AUX_MODE    0x04
#define DOME_MODE   0x05
#define CALL_MODE   0x06


#define BLINK_METHOD_CMD   0x12
/*
 #define POWER_LONG_UART_CMD      0x31
 //#define POWER_LONG_UART_CMD      0xBA

 #define DOME_UART_CMD      0x32

 #define VOL_ADD_UART_CMD      0x36
 #define VOL_MINUS_UART_CMD    0x37

 #define UP_UART_CMD    0x34
 #define DOWN_UART_CMD    0x35

 #define PLAY_UART_CMD    0x38

 #define MODE_UART_CMD    0x39
 */

typedef struct _Uart_ST {

	uint8_t rxBuf[512];
	uint8_t txBuf[256];

	uint16_t pWrite;
	uint16_t pRead;

} Uart_ST;

void app_uart_Init(void);
void app_uart_send(uint8_t cmd, uint8_t *ptr, uint8_t len);
void app_uart_pro(void);

#endif /* APP_INC_APP_UART_H_ */
