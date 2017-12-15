/*
 * app_work.c
 *
 *  Created on: 2017年7月6日
 *      Author: admin
 */

#include "app.h"

WORK_T g_tWork;
static uint8_t i = 0;

static LED_MODE_MSG_ST led_mode_msg;

void app_work_Init(void) {

	memset((uint8_t *) &g_tWork, 0, sizeof(WORK_T));
	memset((uint8_t *) &led_mode_msg, 0, sizeof(LED_MODE_MSG_ST));
}

void app_work_1s_pro(void) {

	if (g_tWork.status.bits.DOME) {
		uint8_t index = 0;
		uint8_t buffer[16] = { 0 };

		index = 0;
		buffer[index++] = LAMP2LCD_HEADER;
		buffer[index++] = 11;
		buffer[index++] = LED_MODE_MSG_CMD;
		buffer[index++] = g_tWork.device_mode;  //蓝牙模块工作模式
		app_dome_get_current_Name(buffer + index, 8);
		index += 8;
		if (g_tWork.status.bits.blinkEnable) {
			led_mode_msg.status.bits.pp = 0;
		} else {
			led_mode_msg.status.bits.pp = 1;
		}
		buffer[index++] = led_mode_msg.status.allbits;
		for (i = 0; i < (buffer[1] + 1); i++) {
			buffer[index] += buffer[i + 1];
		}
		index++;
		app_2d4_send(buffer, index);
	}

}
void app_work_100ms_pro(void) {

}

