/*
 * app_uart.c
 *
 *  Created on: 2017年8月31日
 *      Author: fly
 */

#include "app.h"
#include <string.h>
//#include "Mini58Series.h"

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
//static uint8_t uart_sendBuf[16] = { 0 };

static Uart_ST uart_st;

void app_uart_Init(void) {

	memset((uint8_t *) &uart_st, 0, sizeof(Uart_ST));
}

void app_uart_send(uint8_t cmd, uint8_t *ptr, uint8_t len) {
	uint8_t index = 0, i = 0;

	memset(uart_st.txBuf, 0, sizeof(uart_st.txBuf));

	uart_st.txBuf[index++] = 0x55;
	uart_st.txBuf[index++] = 0xAA;
	uart_st.txBuf[index++] = len + 1;
	uart_st.txBuf[index++] = cmd;
	for (i = 0; i < len; i++) {
		uart_st.txBuf[index++] = *(ptr + i);
	}
	uart_st.txBuf[index++] = app_CalcCRC8(uart_st.txBuf, len + 4);
	comSendBuf(COM1, uart_st.txBuf, index);

//	for (i = 0; i < (len + 5); i++) {
//		comSendChar(uart_st.txBuf[i]);
//	}
}

static void app_RC_Receiver_cmd_pro(Uart_ST* st) {

	uint8_t index = 0;
	uint8_t i = 0;
	uint8_t buffer[PAYLOAD_WIDTH] = { 0 };

	switch (st->rxBuf[(st->pRead + 3) % sizeof(st->rxBuf)]) {
	case BLINK_METHOD_CMD:  //闪法
	{
//		break;
		uint8_t index = st->rxBuf[(st->pRead + 12) % sizeof(st->rxBuf)];
		uint8_t availableGroup = 0;
		uint8_t minSpaceBytes = 0;
		uint8_t bytes = 0;
		if (sizeof(DOME_DEFAULT_T) % 4) {
			minSpaceBytes = (sizeof(DOME_DEFAULT_T) / 4) * 4 + 4;
		} else {
			minSpaceBytes = sizeof(DOME_DEFAULT_T);
		}
		availableGroup = (FMC_APROM_END - DOME_START_ADDR) / minSpaceBytes;

		if (index > (availableGroup - 1)) {
			break;
		}
		FMC_ENABLE_AP_UPDATE();
		SYS_UnlockReg();
		FMC_Open();

		if (index == 0) {
			u8_tmp = (FMC_APROM_END - DOME_START_ADDR) / FMC_FLASH_PAGE_SIZE;
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
		tmp = st->rxBuf[(st->pRead + 13) % sizeof(st->rxBuf)] & 0x0F; //sub mode number

		bytes = tmp * sizeof(SUBDOME_T) + sizeof(DOME_HEADER_T);

//		if (minSpaceBytes % 4) {
//			minSpaceBytes++;
//		}

		for (i = 0; i < (bytes / 4); i++) {
			uint32_t addr = index * minSpaceBytes + i * 4;
			uint32_t dt = st->rxBuf[(st->pRead + 4 + i * 4) % sizeof(st->rxBuf)];
			dt |= st->rxBuf[(st->pRead + 4 + i * 4 + 1) % sizeof(st->rxBuf)]
					<< 8;
			dt |= st->rxBuf[(st->pRead + 4 + i * 4 + 2) % sizeof(st->rxBuf)]
					<< 16;
			dt |= st->rxBuf[(st->pRead + 4 + i * 4 + 3) % sizeof(st->rxBuf)]
					<< 24;
			app_eeprom_write_int(addr, dt);
		}
		if (bytes % 4) {
			uint32_t addr = index * minSpaceBytes + (bytes / 4) * 4;
			uint32_t dt = 0;
			for (i = 0; i < (bytes % 4); i++) {
				switch (i) {
				case 0:
					dt = st->rxBuf[(st->pRead + 4 + (bytes / 4) * 4)
							% sizeof(st->rxBuf)];
					break;
				case 1:
					dt |= st->rxBuf[(st->pRead + 4 + (bytes / 4) * 4 + i)
							% sizeof(st->rxBuf)] << 8;
					break;
				case 2:
					dt |= st->rxBuf[(st->pRead + 4 + (bytes / 4) * 4 + i)
							% sizeof(st->rxBuf)] << 16;
					break;
				}
			}
			app_eeprom_write_int(addr, dt);
		}

#if 1
		blink_number = 0;
		for (i = 0; i < availableGroup; i++) {
			uint32_t add_tmp = i * minSpaceBytes;
			uint32_t add_data = app_eeprom_read_int(add_tmp);
			if (0xFFFFFFFF != add_data) {
				blink_number++;
			} else {
				break;
			}
		}
#endif

		FMC_Close();
		SYS_LockReg();
		FMC_DISABLE_AP_UPDATE();
#endif
		u8_tmp = index & 0xFF;
		app_uart_send(BLINK_METHOD_CMD, &u8_tmp, 1);
	}
		break;
	case RCV_VOL_CMD:
		buffer[index++] = LAMP2LCD_HEADER;
		buffer[index++] = len;
		buffer[index++] = RCV_VOL_CMD;
		for (i = 0; i < (len - 1); i++) {
			buffer[index++] =
					st->rxBuf[(st->pRead + 4 + i) % sizeof(st->rxBuf)];
		}
		for (i = 0; i < (buffer[1] + 1); i++) {
			buffer[index] += buffer[i + 1];
		}
		index++;
		app_2d4_send(buffer, index);
		break;
	case RCV_POWER_STATUS_CMD:
		buffer[index++] = LAMP2LCD_HEADER;
		buffer[index++] = len;
		buffer[index++] = RCV_POWER_STATUS_CMD;
		for (i = 0; i < (len - 1); i++) {
			buffer[index++] =
					st->rxBuf[(st->pRead + 4 + i) % sizeof(st->rxBuf)];
		}
		for (i = 0; i < (buffer[1] + 1); i++) {
			buffer[index] += buffer[i + 1];
		}
		index++;
		app_2d4_send(buffer, index);
		break;
#if 0
		case RCV_X_BOX_STATUS_CMD:
		buffer[index++] = LAMP2LCD_HEADER;
		buffer[index++] = len;
		buffer[index++] = RCV_X_BOX_STATUS_CMD;
		for (i = 0; i < (len - 1); i++) {
			buffer[index++] = st->rxBuf[(st->pRead + 4
					+ i) % sizeof(st->rxBuf)];
		}
		for (i = 0; i < (buffer[1] + 1); i++) {
			buffer[index] += buffer[i + 1];
		}
		index++;
		app_2d4_send(buffer, index);
		break;
#endif
	case RCV_BT_STATUS_CMD:
		g_tWork.device_mode = BT_MODE;
		if (g_tWork.status.bits.DOME) {
			break;
		}
		buffer[index++] = LAMP2LCD_HEADER;
		buffer[index++] = len;
		buffer[index++] = RCV_BT_STATUS_CMD;
		for (i = 0; i < (len - 1); i++) {
			buffer[index++] =
					st->rxBuf[(st->pRead + 4 + i) % sizeof(st->rxBuf)];
		}
		for (i = 0; i < (buffer[1] + 1); i++) {
			buffer[index] += buffer[i + 1];
		}
		index++;
		app_2d4_send(buffer, index);
		break;
	case RCV_PREV_NEXT_CMD:
		if (g_tWork.status.bits.DOME) {
			break;
		}
		buffer[index++] = LAMP2LCD_HEADER;
		buffer[index++] = len;
		buffer[index++] = RCV_PREV_NEXT_CMD;
		for (i = 0; i < (len - 1); i++) {
			buffer[index++] =
					st->rxBuf[(st->pRead + 4 + i) % sizeof(st->rxBuf)];
		}
		for (i = 0; i < (buffer[1] + 1); i++) {
			buffer[index] += buffer[i + 1];
		}
		index++;
		app_2d4_send(buffer, index);
		break;
	case RCV_USB_PLAY_TIME_CMD:
		g_tWork.device_mode = USB_MODE;
		if (g_tWork.status.bits.DOME) {
			break;
		}
		buffer[index++] = LAMP2LCD_HEADER;
		buffer[index++] = len;
		buffer[index++] = RCV_USB_PLAY_TIME_CMD;
		for (i = 0; i < (len - 1); i++) {
			buffer[index++] =
					st->rxBuf[(st->pRead + 4 + i) % sizeof(st->rxBuf)];
		}
		for (i = 0; i < (buffer[1] + 1); i++) {
			buffer[index] += buffer[i + 1];
		}
		index++;
		app_2d4_send(buffer, index);
		break;
	case RCV_FM_HZ_CMD:
		g_tWork.device_mode = FM_MODE;
		if (g_tWork.status.bits.DOME) {
			break;
		}
		buffer[index++] = LAMP2LCD_HEADER;
		buffer[index++] = len;
		buffer[index++] = RCV_FM_HZ_CMD;
		for (i = 0; i < (len - 1); i++) {
			buffer[index++] =
					st->rxBuf[(st->pRead + 4 + i) % sizeof(st->rxBuf)];
		}
		for (i = 0; i < (buffer[1] + 1); i++) {
			buffer[index] += buffer[i + 1];
		}
		index++;
		app_2d4_send(buffer, index);
		break;
	case MODE_CHANGE_CMD:   //MODE
		buffer[index++] = LAMP2LCD_HEADER;
		buffer[index++] = len;
		buffer[index++] = MODE_CHANGE_CMD;
		for (i = 0; i < (len - 1); i++) {
			buffer[index++] =
					st->rxBuf[(st->pRead + 4 + i) % sizeof(st->rxBuf)];
		}
		for (i = 0; i < (buffer[1] + 1); i++) {
			buffer[index] += buffer[i + 1];
		}
		index++;
		app_2d4_send(buffer, index);
		break;
	case RCV_PLAY_PAUSE_STATUS_CMD:
		g_tWork.device_mode = st->rxBuf[(st->pRead + 4) % sizeof(st->rxBuf)];
		if (g_tWork.status.bits.DOME) {
			break;
		}
		buffer[index++] = LAMP2LCD_HEADER;
		buffer[index++] = len;
		buffer[index++] = RCV_PLAY_PAUSE_STATUS_CMD;
		for (i = 0; i < (len - 1); i++) {
			buffer[index++] =
					st->rxBuf[(st->pRead + 4 + i) % sizeof(st->rxBuf)];
		}
		for (i = 0; i < (buffer[1] + 1); i++) {
			buffer[index] += buffer[i + 1];
		}
		index++;
		app_2d4_send(buffer, index);
		break;
	case DEVICE_STA_CMD: {
		uint8_t sta[2] = { 0 };
		memset(sta, 0, sizeof(sta));
		sta[0] |= g_tWork.status.bits.blinkEnable ? 0x80 : 0;
		sta[0] |= g_tWork.status.bits.DEMO ? 0x40 : 0;
		sta[1] |= Relay_IsOn() ? 0x01 : 0;
		app_uart_send(DEVICE_STA_CMD, sta, sizeof(sta));
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
		if (g_tWork.status.bits.DOME == 0) {
			break;
		}
		buffer[index++] = LAMP2LCD_HEADER;
		buffer[index++] = 10;
		buffer[index++] = KEY_POWER_SHORT_CMD;
		if (g_tWork.status.bits.blinkEnable) {
			buffer[index++] = 0;
		} else {
			buffer[index++] = 1;
		}

		app_dome_get_current_Name(buffer + index, 8);
		index += 8;
		for (i = 0; i < (buffer[1] + 1); i++) {
			buffer[index] += buffer[i + 1];
		}
		index++;
		app_2d4_send(buffer, index);
		break;
	case KEY_CARD_DEMO_CMD:
		g_tWork.status.bits.DEMO = 1;
		g_tWork.status.bits.blinkEnable = 1;
		app_dome_start(1);

		break;
	case APP_COLOR_ATLA_CMD:
#if 1
		g_tWork.status.bits.DEMO = 0;
		app_dome_rgb(st->rxBuf[(st->pRead + 4) % sizeof(st->rxBuf)],
				st->rxBuf[(st->pRead + 5) % sizeof(st->rxBuf)],
				st->rxBuf[(st->pRead + 6) % sizeof(st->rxBuf)]);
#else
		app_dome_rgb(0xFFFF, 0xFFFF, 0xFFFF);
#endif
		break;
	case APP_BRIGHT_CMD:
		dome_running_param.bright = st->rxBuf[(st->pRead + 4)
				% sizeof(st->rxBuf)];
		Light_bright_set(st->rxBuf[(st->pRead + 4) % sizeof(st->rxBuf)]);
		break;
	case APP_SPEED_CMD:
		dome_running_param.speed =
				st->rxBuf[(st->pRead + 4) % sizeof(st->rxBuf)];
		break;
	case APP_FLASH_INDEX_CMD:
		g_tWork.status.bits.DEMO = 0;
		g_tWork.status.bits.blinkEnable = 1;
//		app_dome_start_current();
		app_dome_start(st->rxBuf[(st->pRead + 4) % sizeof(st->rxBuf)]);

		break;
	case APP_SWITCH_INDEX_CMD: {
		uint8_t switchData = st->rxBuf[(st->pRead + 4) % sizeof(st->rxBuf)];
		if (((switchData >> 4) & 0x0F) == 0) {
			Relay_set(switchData & 0x0F);
		}
	}
		break;
		/// app --end
	default:
		break;
	}

}

void app_uart_pro(uint8_t mc) {
	uint8_t ucData = 0;

#if 1
	while (1) {

		if (comGetChar(COM1, &ucData)) {
#if 0
//			comSendChar(COM0, ucData);
//			log_debug("rcv %02X", ucData);
#endif

			if (mc == 0) {
				return;
			}

			uart_st.rxBuf[uart_st.pWrite++] = ucData;
			if (uart_st.pWrite >= sizeof(uart_st.rxBuf)) {
				uart_st.pWrite = 0;
			}

			/*
			 (0x55,0xAA)...0x00......0x00...0x00,0x00...0x00
			 Head..........Length....cmd....Data........crc8()
			 */
			if ((uart_st.pWrite + sizeof(uart_st.rxBuf) - uart_st.pRead)
					% sizeof(uart_st.rxBuf) > 5) {
				if (((uart_st.rxBuf[uart_st.pRead]) == 0x55)
						&& ((uart_st.rxBuf[(uart_st.pRead + 1)
								% sizeof(uart_st.rxBuf)]) == 0xAA)) {
					len = uart_st.rxBuf[(uart_st.pRead + 2)
							% sizeof(uart_st.rxBuf)];
					if ((uart_st.pWrite + sizeof(uart_st.rxBuf) - uart_st.pRead)
							% sizeof(uart_st.rxBuf) >= (len + 4)) {
						if (uart_st.rxBuf[(uart_st.pRead + len + 3)
								% sizeof(uart_st.rxBuf)]
								!= app_CalcCRC8_cycle(
										uart_st.rxBuf + uart_st.pRead, len + 3,
										uart_st.pRead, sizeof(uart_st.rxBuf))) {
							uart_st.pRead++;
							log_err(
									"[ERROR]   remote control check error!\r\n");
						} else {
							/* your code */
							app_RC_Receiver_cmd_pro(&uart_st);
							uart_st.pRead += len + 4;
							uart_st.pRead = uart_st.pRead
									% sizeof(uart_st.rxBuf);
						}
					}
				} else {
					uart_st.pRead++;
				}
				uart_st.pRead = uart_st.pRead % sizeof(uart_st.rxBuf);
			}
			continue;
		}
		break;

	}
#else
	while (riflag) {
		riflag--;
		if ((st.pWrite + RCV_BUFSIZE - st.pRead) % RCV_BUFSIZE >= 4) {
			if (((st.rxBuf[st.pRead]) == 0x55)
					&& ((st.rxBuf[(st.pRead + 1) % RCV_BUFSIZE]) == 0xAA)) {
				len = st.rxBuf[(st.pRead + 2) % RCV_BUFSIZE];
				if ((st.pWrite + RCV_BUFSIZE - st.pRead) % RCV_BUFSIZE
						>= (len + 4)) {
					if (st.rxBuf[(st.pRead + len + 3) % RCV_BUFSIZE]
							!= app_CalcCRC8_cycle(st.rxBuf + st.pRead,
									len + 3, st.pRead, RCV_BUFSIZE)) {
						st.pRead++;
					} else {
						uint8_t index = 0;
						memset(sendBuf, 0, PAYLOAD_WIDTH);
						switch (st.rxBuf[(st.pRead + 3) % RCV_BUFSIZE]) {
							case BLINK_METHOD_CMD:  //闪法
							{
								uint8_t i = 0;
								uint16_t index = 0;
								index =
								st.rxBuf[(st.pRead + 12) % RCV_BUFSIZE];

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
								tmp = st.rxBuf[(st.pRead + 13) % RCV_BUFSIZE]
								& 0x0F;  //sub mode number

								uint8_t n = (tmp * sizeof(SUBDOME_T)
										+ sizeof(DOME_HEADER_T));
								uint8_t minSpaceBytes = sizeof(DOME_DEFAULT_T);
								if (minSpaceBytes % 4) {
									minSpaceBytes++;
								}

								for (i = 0; i < (n / 4); i++) {
									uint32_t addr = index * minSpaceBytes + i * 4;
									uint32_t dt = st.rxBuf[(st.pRead + 4 + i)
									% RCV_BUFSIZE];
									dt |= st.rxBuf[(st.pRead + 4 + i + 1)
									% RCV_BUFSIZE] << 8;
									dt |= st.rxBuf[(st.pRead + 4 + i + 2)
									% RCV_BUFSIZE] << 16;
									dt |= st.rxBuf[(st.pRead + 4 + i + 3)
									% RCV_BUFSIZE] << 24;
									app_eeprom_write_int(addr, dt);
								}
								for (i = 0; i < (n % 4); i++) {
									uint32_t addr = index * minSpaceBytes + n / 4
									+ 4;
									uint32_t dt = 0;
									switch (i) {
										case 0:
										dt = st.rxBuf[(st.pRead + 4 + n / 4)
										% RCV_BUFSIZE];
										break;
										case 1:
										dt |= st.rxBuf[(st.pRead + 4 + n / 4
												+ i) % RCV_BUFSIZE] << 8;
										break;
										case 2:
										dt |= st.rxBuf[(st.pRead + 4 + n / 4
												+ i) % RCV_BUFSIZE] << 16;
										break;
										case 3:
										dt |= st.rxBuf[(st.pRead + 4 + n / 4
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
								sendBuf[index++] = st.rxBuf[(st.pRead + 4
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
								sendBuf[index++] = st.rxBuf[(st.pRead + 4
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
								sendBuf[index++] = st.rxBuf[(st.pRead + 4
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
								sendBuf[index++] = st.rxBuf[(st.pRead + 4
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
								sendBuf[index++] = st.rxBuf[(st.pRead + 4
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
								sendBuf[index++] = st.rxBuf[(st.pRead + 4
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
								sendBuf[index++] = st.rxBuf[(st.pRead + 4
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
								sendBuf[index++] = st.rxBuf[(st.pRead + 4
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
								sendBuf[index++] = st.rxBuf[(st.pRead + 4
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
									st.rxBuf[(st.pRead + 4) % RCV_BUFSIZE],
									st.rxBuf[(st.pRead + 5) % RCV_BUFSIZE],
									st.rxBuf[(st.pRead + 6) % RCV_BUFSIZE]);
#else
							app_dome_rgb(0xFFFF, 0xFFFF, 0xFFFF);
#endif
							break;
							case APP_BRIGHT_CMD:
							dome_running_param.bright = st.rxBuf[(st.pRead
									+ 4) % RCV_BUFSIZE];
							Light_bright_set(
									st.rxBuf[(st.pRead + 4) % RCV_BUFSIZE]);
							break;
							case APP_SPEED_CMD:
							dome_running_param.speed = st.rxBuf[(st.pRead
									+ 4) % RCV_BUFSIZE];
							break;
							case APP_FLASH_INDEX_CMD:
							g_tWork.status.bits.DEMO = 0;
							app_dome_start_current();
							app_dome_start(
									st.rxBuf[(st.pRead + 4) % RCV_BUFSIZE],
									0);
							break;
							case APP_SWITCH_INDEX_CMD: {
								uint8_t switchData = st.rxBuf[(st.pRead + 4)
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
						st.pRead += len + 4;
#if 1
						st.pRead = st.pRead % RCV_BUFSIZE;
//						break;
						return;
#endif
					}
				}
			} else {
				st.pRead++;
			}
			st.pRead = st.pRead % RCV_BUFSIZE;
		}
	}
#endif
}
