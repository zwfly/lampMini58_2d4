/*
 * app_work.h
 *
 *  Created on: 2017年7月6日
 *      Author: admin
 */

#ifndef APP_INC_APP_WORK_H_
#define APP_INC_APP_WORK_H_

typedef struct _WORK_T {

	uint8_t device_mode;
	union {
		uint8_t allbits;
		struct {
			unsigned DOME :1;
			unsigned ra2 :1;
			unsigned DEMO :1;
			unsigned blinkEnable :1;
			unsigned ra6 :1;
			unsigned ra7 :1;
			unsigned ra8 :1;
			unsigned ra9 :1;
		} bits;
	} status;

//	uint8_t mode;

} WORK_T;

typedef struct _LED_MODE_MSG_ST {

	union {
		uint8_t allbits;
		struct {
			unsigned pp :1;  //闪法关闭/开启。0：闪法正常工作，1：闪法暂停
			unsigned ra2 :1;
			unsigned ra3 :1;
			unsigned ra5 :1;
			unsigned ra6 :1;
			unsigned ra7 :1;
			unsigned ra8 :1;
			unsigned ra9 :1;
		} bits;
	} status;

//	uint8_t mode;

} LED_MODE_MSG_ST;

extern WORK_T g_tWork;

void app_work_Init(void);
void app_work_1s_pro(void);
void app_work_100ms_pro(void);

#endif /* APP_INC_APP_WORK_H_ */
