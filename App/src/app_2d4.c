/*
 * app_2d4.c
 *
 *  Created on: 2017年8月16日
 *      Author: fly
 */
#include "app.h"
#include <string.h>
#include <ctype.h>

#include "app_2d4.h"

static uint8_t sendRcv_flag = 0; //0 rcv， 1 send
static uint8_t rcvBuf[PAYLOAD_WIDTH] = { 0 };
uint8_t sendBuf[PAYLOAD_WIDTH] = { 0 };

uint8_t tmpBuf[8] = { 0 };

//static uint8_t test_vol = 0;
//static uint8_t test_yinxiang_status = 0;

void app_2d4_init(void) {

	sendRcv_flag = 0;
	memset(rcvBuf, 0, sizeof(rcvBuf));
	memset(sendBuf, 0, sizeof(sendBuf));

	RF_Init();
#if 1

	RF_RxMode();
#else
	RF_TxMode();
	sendRcv_flag = 1;
#endif

//	RF_Carrier(1);

}

void app_2d4_send(uint8_t *d, uint8_t len) {
//	if (len > PAYLOAD_WIDTH) {
//		return;
//	}
	uint16_t i = 0;
	for (i = 0; i < 20; i++) {
		nop
		nop
		nop
//		nop
	}
	RF_TxMode();
	sendRcv_flag = 1;

	for (i = 0; i < 200; i++) {
		nop
		nop
		nop
		nop
	}

	if (sendBuf != d) {
		memset(sendBuf, 0, PAYLOAD_WIDTH);
		memcpy(sendBuf, d, len);
	}
}
#if DEBUG
idata char sss[32] = {0};
#endif
static void app_2d4_Rcv(uint8_t *buf) {
	uint8_t tmp = 0;
	uint8_t i = 0;
	uint8_t index = 0;
	uint8_t check = 0;
#if DEBUG
	sprintf(sss, "rcv %02X %02X %02X %02X %02X %02X\r\n", (uint16_t) buf[0],
			(uint16_t) buf[1], (uint16_t) buf[2], (uint16_t) buf[3],
			(uint16_t) buf[4], (uint16_t) buf[5]);
	printf(sss);
#endif
	if (buf[0] != LCD2LAMP_HEADER) {
		return;
	}
	if (buf[1] > sizeof(rcvBuf)) {
		return;
	}
	for (i = 0; i < (buf[1] + 1); i++) {
		check += buf[i + 1];
	}
	if (check != buf[buf[1] + 2]) {
		return;
	}

	memset(sendBuf, 0, PAYLOAD_WIDTH);
	index = 0;
	switch (buf[2]) {
	case KEY_POWER_SHORT_CMD:
//		if (g_tWork.status.bits.DOME) {
//			if (g_tWork.status.bits.pause) {
//				g_tWork.status.bits.pause = 0;
//				app_dome_start_current();
//			} else {
//				g_tWork.status.bits.pause = 1;
//				app_dome_stop_current();
//			}
//			sendBuf[index++] = LAMP2LCD_HEADER;
//			sendBuf[index++] = 10;
//			sendBuf[index++] = KEY_POWER_SHORT_CMD;
//			sendBuf[index++] = g_tWork.status.bits.pause;
//			app_dome_get_current_Name(sendBuf + index, 8);
//			index += 8;
//			for (i = 0; i < (sendBuf[1] + 1); i++) {
//				sendBuf[index] += sendBuf[i + 1];
//			}
//			index++;
//			app_2d4_send(sendBuf, index);
//
//		} else {
		app_uart_send(KEY_POWER_SHORT_CMD, 0, 0);
//		}
		break;
#if 0
		case POWER_LONG_CMD:
#if 0
		if (buf[3] == 1) {
			test_yinxiang_status = 1;
		} else if (buf[3] == 2) {
			test_yinxiang_status = 0;
		} else if (buf[3] == 3) {
			if (test_yinxiang_status) {
				test_yinxiang_status = 0;
			} else {
				test_yinxiang_status = 1;
			}
		}
		sendBuf[index++] = LAMP2LCD_HEADER;
		sendBuf[index++] = 0x02;
		sendBuf[index++] = buf[2];
		sendBuf[index++] = test_yinxiang_status;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
#else
		//	tmp = 0x03;
		//	app_uart_send(POWER_LONG_UART_CMD, &tmp, 1);

#endif
		break;
#endif
	case KEY_ACC_CMD:
		if (buf[3] == 1) {
			Relay_on();
		} else if (buf[3] == 2) {
			Relay_off();
		} else if (buf[3] == 3) {
			Relay_toggle();
		}
		sendBuf[index++] = LAMP2LCD_HEADER;
		sendBuf[index++] = 0x02;
		sendBuf[index++] = buf[2];
		if (Relay_IsOn()) {
			sendBuf[index++] = 0x01;
		} else {
			sendBuf[index++] = 0x02;
		}
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_UP_CMD:
		if (g_tWork.status.bits.DOME) {
			app_dome_start_current();
			g_tWork.status.bits.DEMO = 0;
			if (g_tWork.status.bits.blinkEnable) {
				app_dome_previous();
				sendBuf[index++] = LAMP2LCD_HEADER;
				sendBuf[index++] = 9;
				sendBuf[index++] = KEY_UP_CMD;
				app_dome_get_current_Name(sendBuf + index, 8);
				index += 8;
				for (i = 0; i < (sendBuf[1] + 1); i++) {
					sendBuf[index] += sendBuf[i + 1];
				}
				index++;
				app_2d4_send(sendBuf, index);
			}
		} else {
			app_uart_send(KEY_UP_CMD, 0, 0);
		}
		break;
	case KEY_DOWN_CMD:
		if (g_tWork.status.bits.DOME) {
			app_dome_start_current();
			g_tWork.status.bits.DEMO = 0;
			if (g_tWork.status.bits.blinkEnable) {
				app_dome_next();
				sendBuf[index++] = LAMP2LCD_HEADER;
				sendBuf[index++] = 9;
				sendBuf[index++] = KEY_DOWN_CMD;
				app_dome_get_current_Name(sendBuf + index, 8);
				index += 8;
				for (i = 0; i < (sendBuf[1] + 1); i++) {
					sendBuf[index] += sendBuf[i + 1];
				}
				index++;
				app_2d4_send(sendBuf, index);
			}
		} else {
			app_uart_send(KEY_DOWN_CMD, 0, 0);
		}
		break;
	case RCV_PREV_NEXT_CMD:

		break;
	case KEY_DOME_CMD:

//		tmp = 0x03;
//		app_uart_send(DOME_UART_CMD, &tmp, 1);

		if (g_tWork.status.bits.DOME) {
			g_tWork.status.bits.DOME = 0;
		} else {
			g_tWork.status.bits.DOME = 1;
		}
		sendBuf[index++] = LAMP2LCD_HEADER;
		sendBuf[index++] = 11;
		sendBuf[index++] = KEY_DOME_CMD;
		sendBuf[index++] = g_tWork.status.bits.DOME;
		sendBuf[index++] = g_tWork.status.bits.blinkEnable;
		app_dome_get_current_Name(sendBuf + index, 8);
		for (i = 0; i < 8; i++) {
			if ((*(sendBuf + index + i) == 0)
					|| (*(sendBuf + index + i) == 0xFF)) {
				*(sendBuf + index + i) = ' ';
			}
		}
		index += 8;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		index++;
		app_2d4_send(sendBuf, index);
		break;
	case KEY_VOL_ADD_CMD:
		app_uart_send(KEY_VOL_ADD_CMD, 0, 0);
		break;
	case KEY_VOL_MINUS_CMD:
		app_uart_send(KEY_VOL_MINUS_CMD, 0, 0);
		break;
	case KEY_PLAY_SHORT_CMD:
		app_uart_send(KEY_PLAY_SHORT_CMD, 0, 0);
		break;
	case KEY_PLAY_LONG_CMD:
		app_uart_send(KEY_PLAY_LONG_CMD, 0, 0);
		break;
	case KEY_MODE_CMD:
		app_uart_send(KEY_MODE_CMD, 0, 0);
		break;
		/// card --start
	case KEY_CARD_MODE_POWER_CMD:
		app_uart_send(KEY_MODE_CMD, 0, 0);
		break;
	case KEY_CARD_MODE_POWER_LONG_CMD:
		app_uart_send(KEY_POWER_SHORT_CMD, 0, 0);
		break;
	case KEY_CARD_PREV_VOL_MINUS_CMD:
		app_uart_send(KEY_UP_CMD, 0, 0);
		break;
	case KEY_CARD_PREV_VOL_MINUS_LONG_CMD:
		app_uart_send(KEY_VOL_MINUS_CMD, 0, 0);
		break;
	case KEY_CARD_PLAY_BT_CALL_CMD:
		app_uart_send(KEY_PLAY_SHORT_CMD, 0, 0);
		break;
	case KEY_CARD_PLAY_BT_CALL_LONG_CMD:

		break;
	case KEY_CARD_NEXT_VOL_ADD_CMD:
		app_uart_send(KEY_DOWN_CMD, 0, 0);
		break;
	case KEY_CARD_NEXT_VOL_ADD_LONG_CMD:
		app_uart_send(KEY_VOL_ADD_CMD, 0, 0);
		break;
	case KEY_CARD_POWER_CMD:
		if (g_tWork.status.bits.blinkEnable == 0) {
			g_tWork.status.bits.blinkEnable = 1;
			g_tWork.status.bits.DEMO = 1;

			app_dome_start(0, 0);
//			app_dome_start_current();
		} else {
			g_tWork.status.bits.blinkEnable = 0;
			g_tWork.status.bits.DEMO = 0;

			g_tWork.status.bits.blinkEnable = 1;
			app_dome_stop_current();
		}
		sendBuf[index++] = LAMP2LCD_HEADER;
		sendBuf[index++] = 10;
		sendBuf[index++] = KEY_POWER_SHORT_CMD;
		sendBuf[index++] = g_tWork.status.bits.blinkEnable;
		app_dome_get_current_Name(sendBuf + index, 8);
		for (i = 0; i < 8; i++) {
			if ((*(sendBuf + index + i) == 0)
					|| (*(sendBuf + index + i) == 0xFF)) {
				*(sendBuf + index + i) = ' ';
			}
		}
		index += 8;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		index++;
		app_2d4_send(sendBuf, index);
		break;
	case KEY_CARD_MODE_ADD_CMD:
		g_tWork.status.bits.DEMO = 0;
		app_dome_start_current();
		app_dome_next();
		break;
	case KEY_CARD_SPEED_ADD_CMD:
		if (dome_running_param.speed <= 100) {
			dome_running_param.speed += 10;
			if (dome_running_param.speed >= 100) {
				dome_running_param.speed = 100;
			}
		}
		break;
	case KEY_CARD_DEMO_CMD:
//		if (g_tWork.status.bits.DEMO) {
//			g_tWork.status.bits.DEMO = 0;
//		} else {
		g_tWork.status.bits.DEMO = 1;
//		}
		app_dome_start(0, 0);
		break;
	case KEY_CARD_SPEED_MINUS_CMD:
		if (dome_running_param.speed >= 10) {
			dome_running_param.speed -= 10;
		}
		break;
	case KEY_CARD_COLOR_ADD_CMD:
		app_color_blink_next();
		break;
	case KEY_CARD_MODE_CMD:

		g_tWork.status.bits.DEMO = 0;
		app_dome_start_current();
		app_dome_previous();
		break;
	case KEY_CARD_BRIGHT_ADD_CMD:
		if (dome_running_param.bright <= 100) {
			dome_running_param.bright += 10;
			if (dome_running_param.bright >= 100) {
				dome_running_param.bright = 100;
			}
		}
		Light_bright_set(dome_running_param.bright);
		break;
	case KEY_CARD_COLOR_MINUS_CMD:
		app_color_blink_previous();
		break;
	case KEY_CARD_BRIGHT_MINUS_CMD:
		if (dome_running_param.bright >= 10) {
			dome_running_param.bright -= 10;
		}
		Light_bright_set(dome_running_param.bright);

		break;
	case KEY_CARD_NUM_1_CMD:
		Relay_toggle();
		sendBuf[index++] = LAMP2LCD_HEADER;
		sendBuf[index++] = 0x02;
		sendBuf[index++] = KEY_ACC_CMD;
		if (Relay_IsOn()) {
			sendBuf[index++] = 0x01;
		} else {
			sendBuf[index++] = 0x02;
		}
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_CARD_NUM_1_LONG_CMD:
		break;
	case KEY_CARD_NUM_2_CMD:

//		Repeat_Start(5,1,1);

		break;
	case KEY_CARD_NUM_3_CMD:
		break;
	case KEY_CARD_NUM_4_CMD:
		break;

		/// card --end
	}
	if (index) {
		index++;
		app_2d4_send(sendBuf, index);
	}

}

void app_2d4_pro(void) {

	if (sendRcv_flag) {

		switch (ucRF_GetStatus()) {
		case TX_DS_FLAG: 		// 普通型发送完成 或 增强型发送成功

			RF_ClearFIFO();
			RF_ClearStatus();

			sendRcv_flag = 0;
			RF_RxMode();

//			Relay_toggle();

			break;
		case RX_DR_FLAG:		//发送成功且收到payload

			RF_ClearFIFO();
			RF_ClearStatus();
			break;
		case MAX_RT_FLAG:		// 增强型发送超时失败

			RF_ClearFIFO();
			RF_ClearStatus();
			break;
		default:		// rf 处于空闲状态才发送数据

			RF_TxData(sendBuf, sizeof(sendBuf));

			break;
		}

	} else {
		if (ucRF_DumpRxData(rcvBuf, sizeof(rcvBuf))) {
			app_2d4_Rcv(rcvBuf);
		}
	}
}

