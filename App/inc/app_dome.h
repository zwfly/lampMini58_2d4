/*
 * app_dome.h
 *
 *  Created on: 2017年9月8日
 *      Author: fly
 */

#ifndef APP_INC_APP_DOME_H_
#define APP_INC_APP_DOME_H_

//#define DOME_SPEED_MULTIPLE   2
//#define DEFAULT_DOME_NUM   22  //use 2.5KB
//#define DEFAULT_DOME_NUM   26  //use 3KB
//#define DEFAULT_DOME_NUM   44  //use 5KB

#pragma pack(1)
typedef struct _DOME_PRO_T {
	uint8_t currentDomeIndex;
//	uint8_t currentSubDomeIndex;

} DOME_PRO_T;
#pragma pack()

#pragma pack(1)
typedef struct _SUBDOME_ASSIST_T {
	uint8_t switch_flag;
	uint32_t msCnt;
	uint8_t stopTime;
} SUBDOME_ASSIST_T;
#pragma pack()
///////
#pragma pack(1)
typedef struct _COLOR_T {
	uint8_t R;
	uint8_t G;
	uint8_t B;
} COLOR_T;
#pragma pack()

#pragma pack(1)
typedef struct _SUBDOME_T {
	uint8_t mode;
	COLOR_T color1;
	COLOR_T color2;
	uint8_t repeate;
	uint8_t bright;
	uint16_t speed;
	uint16_t offtime;
} SUBDOME_T;
#pragma pack()
//typedef union _REPEAT_NUMBER_T {
//	uint8_t datas;
//	struct {
//		unsigned repeat :4;
//		unsigned number :4;
//	} bits;
//} REPEAT_NUMBER_T;

#pragma pack(1)
typedef struct _DOME_HEADER_T {
	char name[8];
	uint8_t index;  //刚加的
	uint8_t repeat_number;  //闪法重复的次数，单元模式的数量
} DOME_HEADER_T;
#pragma pack()

#pragma pack(1)
typedef struct _DOME_DEFAULT_T {
	DOME_HEADER_T header;
	SUBDOME_T subdome[8];
} DOME_DEFAULT_T;
#pragma pack()

#pragma pack(1)
typedef struct _DOME_RUNNING_T {
	uint8_t bright;
	uint8_t speed;
	struct {
		uint16_t R;
		uint16_t G;
		uint16_t B;
	} color;
} DOME_RUNNING_T;
#pragma pack()

extern uint8_t blink_number; //闪法的总数量
extern DOME_DEFAULT_T dome_blink;
extern DOME_RUNNING_T dome_running_param;

void app_dome_Init(void);

void app_color_blink_previous(void);
void app_color_blink_next(void);

void app_dome_start(uint8_t index, uint8_t dir);
void app_dome_previous(void);
void app_dome_next(void);
void app_dome_get_current_Name(uint8_t *name, uint8_t len);
void app_dome_start_current(void);
void app_dome_stop_current(void);
void app_dome_rgb(uint8_t r, uint8_t g, uint8_t b);
void app_dome_interrupter(void);

#endif /* APP_INC_APP_DOME_H_ */
