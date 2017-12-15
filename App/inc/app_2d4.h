/*
 * app_2d4.h
 *
 *  Created on: 2017Äê8ÔÂ18ÈÕ
 *      Author: fly
 */

#ifndef APP_INC_APP_2D4_H_
#define APP_INC_APP_2D4_H_

#define LCD2LAMP_HEADER   0xF2
#define LAMP2LCD_HEADER   0xF8
/*
 #define POWER_SHORT_CMD      0xB1
 #define POWER_LONG_CMD      0xBA

 #define ACC_CMD        0xB6

 #define UP_CMD         0xB3
 #define DOWN_CMD       0xB4
 #define DOME_CMD       0xB9
 #define VOL_ADD_CMD    0xB5
 #define VOL_MINUS_CMD  0xB7

 #define PLAY_CMD       0xB2
 #define MODE_CMD       0xB8
 */
/////////
#define  KEY_POWER_SHORT_CMD      0x01
//#define POWER_LONG_CMD      0xBA

#define  KEY_ACC_CMD        0x09
#define  KEY_DOME_CMD       0xB9

#define  KEY_UP_CMD           0x02
#define  KEY_DOWN_CMD         0x03
#define  KEY_VOL_ADD_CMD      0x04
#define  KEY_VOL_MINUS_CMD    0x05
#define  KEY_PLAY_SHORT_CMD   0x06
#define  KEY_PLAY_LONG_CMD    0x07
#define  KEY_MODE_CMD         0x08
///

#define  RCV_POWER_STATUS_CMD                0x31
#define  RCV_X_BOX_STATUS_CMD                0x32
#define  RCV_BT_STATUS_CMD                   0x33
#define  RCV_PLAY_PAUSE_STATUS_CMD           0x34
#define  RCV_PREV_NEXT_CMD                   0x35

#define  RCV_USB_PLAY_TIME_CMD               0x36
#define  RCV_FM_HZ_CMD                       0x37
#define  RCV_VOL_CMD                         0x38

#define  MODE_CHANGE_CMD                     0x41

#define  KEY_CARD_MODE_POWER_CMD           0x50
#define  KEY_CARD_MODE_POWER_LONG_CMD      0x70
#define  KEY_CARD_PREV_VOL_MINUS_CMD       0x51
#define  KEY_CARD_PREV_VOL_MINUS_LONG_CMD  0x71
#define  KEY_CARD_PLAY_BT_CALL_CMD         0x52
#define  KEY_CARD_PLAY_BT_CALL_LONG_CMD    0x72
#define  KEY_CARD_NEXT_VOL_ADD_CMD         0x53
#define  KEY_CARD_NEXT_VOL_ADD_LONG_CMD    0x73

#define  KEY_CARD_POWER_CMD              0x54
#define  KEY_CARD_MODE_ADD_CMD           0x55

#define  KEY_CARD_SPEED_ADD_CMD          0x56
#define  KEY_CARD_DEMO_CMD               0x57
#define  KEY_CARD_SPEED_MINUS_CMD        0x58

#define  KEY_CARD_COLOR_ADD_CMD          0x59
#define  KEY_CARD_MODE_CMD               0x5A
#define  KEY_CARD_BRIGHT_ADD_CMD         0x5B

#define  KEY_CARD_COLOR_MINUS_CMD        0x5C
#define  KEY_CARD_BRIGHT_MINUS_CMD       0x5D

#define  KEY_CARD_NUM_1_CMD              0x5E
#define  KEY_CARD_NUM_1_LONG_CMD         0x7E
#define  KEY_CARD_NUM_2_CMD              0x5F
#define  KEY_CARD_NUM_3_CMD              0x60
#define  KEY_CARD_NUM_4_CMD              0x61

#define  APP_COLOR_ATLA_CMD       0x62
#define  APP_BRIGHT_CMD           0x63
#define  APP_SPEED_CMD            0x64
#define  APP_FLASH_INDEX_CMD      0x65
#define  APP_SWITCH_INDEX_CMD      0x66

#define  LED_MODE_MSG_CMD      0xE0

#define  DEVICE_STA_CMD      0xF0
//extern uint8_t sendBuf[PAYLOAD_WIDTH];

void app_2d4_init(void);
void app_2d4_send(uint8_t *d, uint8_t len);
void app_2d4_pro(void);

#endif /* APP_INC_APP_2D4_H_ */
