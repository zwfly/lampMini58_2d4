/*
 * app_uart.c
 *
 *  Created on: 2017年8月31日
 *      Author: fly
 */

#include "app.h"
#include <string.h>

#define BT_MODE     0x01
#define FM_MODE     0x02
#define USB_MODE    0x03
#define AUX_MODE    0x04
#define DOME_MODE   0x05
#define CALL_MODE   0x06

//static uint8_t index = 0;
static uint8_t len = 0;
//static uint8_t i = 0, j = 0;
static uint16_t tmp = 0;
static uint8_t u8_tmp = 0;
static uint8_t uart_sendBuf[16] = { 0 };

void app_uart_Init(void) {

	memset((uint8_t *) &rcv_T, 0, sizeof(RCV_T));
}

void app_uart_send(uint8_t cmd, uint8_t *ptr, uint8_t len) {
	uint8_t index = 0, i = 0;

	uart_sendBuf[index++] = 0x55;
	uart_sendBuf[index++] = 0xAA;
	uart_sendBuf[index++] = len + 1;
	uart_sendBuf[index++] = cmd;
	for (i = 0; i < len; i++) {
		uart_sendBuf[index++] = *(ptr + i);
	}
	uart_sendBuf[index++] = app_CalcCRC8(uart_sendBuf, len + 4);

	for (i = 0; i < (len + 5); i++) {
		Send_Data_To_UART0(uart_sendBuf[i]);
	}
}

void app_uart_pro(void) {
	while (riflag) {
		riflag--;
		if ((rcv_T.pWrite + RCV_BUFSIZE - rcv_T.pRead) % RCV_BUFSIZE >= 4) {
			if (((rcv_T.rxBuf[rcv_T.pRead]) == 0x55)
					&& ((rcv_T.rxBuf[(rcv_T.pRead + 1) % RCV_BUFSIZE]) == 0xAA)) {
				len = rcv_T.rxBuf[(rcv_T.pRead + 2) % RCV_BUFSIZE];
				if ((rcv_T.pWrite + RCV_BUFSIZE - rcv_T.pRead) % RCV_BUFSIZE
						>= (len + 4)) {
					if (rcv_T.rxBuf[(rcv_T.pRead + len + 3) % RCV_BUFSIZE]
							!= app_CalcCRC8_cycle(rcv_T.rxBuf + rcv_T.pRead,
									len + 3, rcv_T.pRead, RCV_BUFSIZE)) {
						rcv_T.pRead++;
					} else {
						uint8_t index = 0;
						memset(sendBuf, 0, PAYLOAD_WIDTH);
						switch (rcv_T.rxBuf[(rcv_T.pRead + 3) % RCV_BUFSIZE]) {
						case BLINK_METHOD_CMD:  //闪法
						{
							uint8_t i = 0;
							uint16_t index = 0;
							index =
									rcv_T.rxBuf[(rcv_T.pRead + 12) % RCV_BUFSIZE];

							if (index
									>= ((FMC_APROM_END - DOME_START_ADDR)
											/ sizeof(DOME_DEFAULT_T) - 1)) {
								break;
							}
							FMC_ENABLE_AP_UPDATE();
							SYS_UnlockReg();
							FMC_Open();

							if (index == 0) {
								u8_tmp = (FMC_APROM_END - DOME_START_ADDR)
										/ FMC_FLASH_PAGE_SIZE;
								for (i = 0; i < u8_tmp; i++) {
									app_eeprom_erase(i * FMC_FLASH_PAGE_SIZE);
								}
							}
#if 0
							for (i = (index + 1); i < DEFAULT_DOME_NUM; i++) {
								uint16_t addr = i * sizeof(DOME_DEFAULT_T)
								+ (&dome_blink.header.index
										- &dome_blink);
								app_eeprom_write_byte(addr, 0);
								nop
							}
#endif
#if 1
							tmp = rcv_T.rxBuf[(rcv_T.pRead + 13) % RCV_BUFSIZE]
									& 0x0F;  //sub mode number

							uint8_t n = (tmp * sizeof(SUBDOME_T)
									+ sizeof(DOME_HEADER_T));
							uint8_t minSpaceBytes = sizeof(DOME_DEFAULT_T);
							if (minSpaceBytes % 4) {
								minSpaceBytes++;
							}

							for (i = 0; i < (n / 4); i++) {
								uint32_t addr = index * minSpaceBytes + i * 4;
								uint32_t dt = rcv_T.rxBuf[(rcv_T.pRead + 4 + i)
										% RCV_BUFSIZE];
								dt |= rcv_T.rxBuf[(rcv_T.pRead + 4 + i + 1)
										% RCV_BUFSIZE] << 8;
								dt |= rcv_T.rxBuf[(rcv_T.pRead + 4 + i + 2)
										% RCV_BUFSIZE] << 16;
								dt |= rcv_T.rxBuf[(rcv_T.pRead + 4 + i + 3)
										% RCV_BUFSIZE] << 24;
								app_eeprom_write_int(addr, dt);
							}
							for (i = 0; i < (n % 4); i++) {
								uint32_t addr = index * minSpaceBytes + n / 4
										+ 4;
								uint32_t dt = 0;
								switch (i) {
								case 0:
									dt = rcv_T.rxBuf[(rcv_T.pRead + 4 + n / 4)
											% RCV_BUFSIZE];
									break;
								case 1:
									dt |= rcv_T.rxBuf[(rcv_T.pRead + 4 + n / 4
											+ i) % RCV_BUFSIZE] << 8;
									break;
								case 2:
									dt |= rcv_T.rxBuf[(rcv_T.pRead + 4 + n / 4
											+ i) % RCV_BUFSIZE] << 16;
									break;
								case 3:
									dt |= rcv_T.rxBuf[(rcv_T.pRead + 4 + n / 4
											+ i) % RCV_BUFSIZE] << 24;
									break;
								}
								app_eeprom_write_int(addr, dt);
							}

							FMC_Close();
							SYS_LockReg();
							FMC_DISABLE_AP_UPDATE();
#endif
							u8_tmp = index & 0xFF;
							app_uart_send(BLINK_METHOD_CMD, &u8_tmp, 1);
						}
							break;
						case RCV_VOL_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_VOL_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case RCV_POWER_STATUS_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_POWER_STATUS_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
#if 0
							case RCV_X_BOX_STATUS_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_X_BOX_STATUS_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
#endif
						case RCV_BT_STATUS_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_BT_STATUS_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							if (g_tWork.status.bits.DOME == 0) {
								app_2d4_send(sendBuf, index);
							}
							break;
						case RCV_PREV_NEXT_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_PREV_NEXT_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							if (g_tWork.status.bits.DOME == 0) {
								app_2d4_send(sendBuf, index);
							}
							break;
						case RCV_USB_PLAY_TIME_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_USB_PLAY_TIME_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							if (g_tWork.status.bits.DOME == 0) {
								app_2d4_send(sendBuf, index);
							}
							break;
						case RCV_FM_HZ_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_FM_HZ_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;

							if (g_tWork.status.bits.DOME == 0) {
								app_2d4_send(sendBuf, index);
							}
							break;
						case MODE_CHANGE_CMD:   //MODE
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = MODE_CHANGE_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case RCV_PLAY_PAUSE_STATUS_CMD:
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = len;
							sendBuf[index++] = RCV_PLAY_PAUSE_STATUS_CMD;
							for (i = 0; i < (len - 1); i++) {
								sendBuf[index++] = rcv_T.rxBuf[(rcv_T.pRead + 4
										+ i) % RCV_BUFSIZE];
							}
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							if (g_tWork.status.bits.DOME == 0) {
								app_2d4_send(sendBuf, index);
							}
							break;
							/// app --start
						case KEY_CARD_POWER_CMD:
							if (g_tWork.status.bits.blinkEnable == 0) {
//								g_tWork.status.bits.pause = 0;
								g_tWork.status.bits.blinkEnable = 1;
								g_tWork.status.bits.DEMO = 1;
								app_dome_start_current();
							} else {
//								g_tWork.status.bits.pause = 1;
								g_tWork.status.bits.blinkEnable = 0;
								g_tWork.status.bits.DEMO = 0;
								app_dome_stop_current();
							}
							sendBuf[index++] = LAMP2LCD_HEADER;
							sendBuf[index++] = 10;
							sendBuf[index++] = KEY_POWER_SHORT_CMD;
							sendBuf[index++] = g_tWork.status.bits.blinkEnable;
							app_dome_get_current_Name(sendBuf + index, 8);
							index += 8;
							for (i = 0; i < (sendBuf[1] + 1); i++) {
								sendBuf[index] += sendBuf[i + 1];
							}
							index++;
							app_2d4_send(sendBuf, index);
							break;
						case KEY_CARD_DEMO_CMD:
//							if (g_tWork.status.bits.DEMO) {
//								g_tWork.status.bits.DEMO = 0;
//							} else {
							g_tWork.status.bits.DEMO = 1;
//							}
							app_dome_start(0, 0);

							break;
						case APP_COLOR_ATLA_CMD:
#if 1
							app_dome_rgb(
									rcv_T.rxBuf[(rcv_T.pRead + 4) % RCV_BUFSIZE],
									rcv_T.rxBuf[(rcv_T.pRead + 5) % RCV_BUFSIZE],
									rcv_T.rxBuf[(rcv_T.pRead + 6) % RCV_BUFSIZE]);
#else
							app_dome_rgb(0xFFFF, 0xFFFF, 0xFFFF);
#endif
							break;
						case APP_BRIGHT_CMD:
							dome_running_param.bright = rcv_T.rxBuf[(rcv_T.pRead
									+ 4) % RCV_BUFSIZE];
							Light_bright_set(
									rcv_T.rxBuf[(rcv_T.pRead + 4) % RCV_BUFSIZE]);
							break;
						case APP_SPEED_CMD:
							dome_running_param.speed = rcv_T.rxBuf[(rcv_T.pRead
									+ 4) % RCV_BUFSIZE];
							break;
						case APP_FLASH_INDEX_CMD:
							g_tWork.status.bits.DEMO = 0;
							app_dome_start_current();
							app_dome_start(
									rcv_T.rxBuf[(rcv_T.pRead + 4) % RCV_BUFSIZE],
									0);
							break;
						case APP_SWITCH_INDEX_CMD: {
							uint8_t switchData = rcv_T.rxBuf[(rcv_T.pRead + 4)
									% RCV_BUFSIZE];
							if (((switchData >> 4) & 0x0F) == 0) {
								Relay_set(switchData & 0x0F);
							}
						}
							break;
							/// app --end
						default:
							break;
						}
						rcv_T.pRead += len + 4;
#if 1
						rcv_T.pRead = rcv_T.pRead % RCV_BUFSIZE;
//						break;
						return;
#endif
					}
				}
			} else {
				rcv_T.pRead++;
			}
			rcv_T.pRead = rcv_T.pRead % RCV_BUFSIZE;
		}
	}

}
