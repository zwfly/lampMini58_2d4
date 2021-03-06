/**************************************************************************//**
 * @file     main.c
 * @version  V2.10
 * $Date: 15/06/02 7:45p $
 * @brief    Use GPIO driver to control the GPIO pin direction, control their
 *           high/low state, and how to use GPIO interrupts.
 *
 * @note
 * Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include "app.h"

#define PLL_CLOCK           50000000

void SYS_Init(void) {
	/* Unlock protected registers */
	SYS_UnlockReg();
#if 0
	/* Set P5 multi-function pins for XTAL1 and XTAL2 */
	SYS->P5_MFP &= ~(SYS_MFP_P50_Msk | SYS_MFP_P51_Msk);
	SYS->P5_MFP |= (SYS_MFP_P50_XT1_IN | SYS_MFP_P51_XT1_OUT);

	/*---------------------------------------------------------------------------------------------------------*/
	/* Init System Clock                                                                                       */
	/*---------------------------------------------------------------------------------------------------------*/

	/* Enable external 12MHz XTAL, HIRC */
	CLK->PWRCTL |= CLK_PWRCTL_XTL12M | CLK_PWRCTL_HIRCEN_Msk;

	/* Waiting for clock ready */
	CLK_WaitClockReady(CLK_STATUS_XTLSTB_Msk | CLK_STATUS_HIRCSTB_Msk);

	/* Switch HCLK clock source to XTL */
	CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_XTAL,CLK_CLKDIV_HCLK(1));

	/* STCLK to XTL STCLK to XTL */
	CLK_SetSysTickClockSrc(CLK_CLKSEL0_STCLKSEL_XTAL);
#else

	/* Enable  HIRC */
//	CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk;
	/* Enable HIRC clock (Internal RC 22.1184MHz) */
	CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);

	/* Wait for HIRC clock ready */
	CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

	/* Select HCLK clock source as HIRC and and HCLK source divider as 1 */
	CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV_HCLK(1));

#endif

	/* Set core clock as PLL_CLOCK from PLL */
	CLK_SetCoreClock(PLL_CLOCK);
	/* To update the variable SystemCoreClock */
	SystemCoreClockUpdate();

	/* Lock protected registers */
	SYS_LockReg();
}
static uint8_t matchCode_flag = 0;
/*---------------------------------------------------------------------------------------------------------*/
/* MAIN function                                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
int main(void) {

	uint8_t ucKeyCode;
	uint8_t dome_cnt = 0;

	/* Init System */
	SYS_Init();

#if 1
	LITE_openlog("lamp");
	LITE_set_loglevel(LOG_DEBUG_LEVEL);
#else
	LITE_closelog();
#endif

	bsp_Init();

	log_debug(" CPU @ %dHz\r\n", SystemCoreClock);

	log_debug("+-------------------------------------+ ");
#if 0
	log_debug("+-------------------------------------+ ");

	log_debug("default size: %d", sizeof(DOME_DEFAULT_T));
	log_debug("dome size: %d", sizeof(DOME_RUNNING_T));
	log_debug("header size: %d", sizeof(DOME_HEADER_T));
	log_debug("submode size: %d", sizeof(SUBDOME_T));
	log_debug("color size: %d", sizeof(COLOR_T));
#endif

	/**************/

	app_work_Init();

	app_uart_Init();
	app_dome_Init();

	/**************/

	while (1) {
		if (timer0_taskTimer_get()->flag_1ms) {
			timer0_taskTimer_get()->flag_1ms = 0;
			//////////////////
#if 1
			dome_cnt++;
			if (dome_running_param.speed >= 50) {
				if (dome_cnt > (10 + (dome_running_param.speed - 50) / 3)) {
					dome_cnt = 0;
					app_dome_interrupter();
				}
			} else {
				if (dome_cnt > (10 - (50 - dome_running_param.speed) / 6)) {
					dome_cnt = 0;
					app_dome_interrupter();
				}
			}
#endif
		}

		if (timer0_taskTimer_get()->flag_10ms) {
			timer0_taskTimer_get()->flag_10ms = 0;
			//////////////////
			static uint8_t flag_2d4 = 0;
			if (flag_2d4 == 0) {
				flag_2d4 = 1;
				app_2d4_init();
			}
			bsp_KeyScan();

			app_2d4_pro();

			app_uart_pro(matchCode_flag);

		}
		if (timer0_taskTimer_get()->flag_100ms) {
			timer0_taskTimer_get()->flag_100ms = 0;
			//////////////////

//			app_work_100ms_pro();
//			Repeat_Pro();

		}
		if (timer0_taskTimer_get()->flag_500ms) {
			timer0_taskTimer_get()->flag_500ms = 0;
			//////////////////

			if (matchCode_flag == 0) {
				uint8_t index = 0, i;
				uint8_t buffer[16] = { 0 };
				memset(buffer, 0, 16);

				index = 0;
				buffer[index++] = LAMP2LCD_HEADER;
				buffer[index++] = 0x06;
				buffer[index++] = WIRELESS_MATCH_CODE_CMD;
				app_get_my_address(buffer + index);
				index += 5;
				for (i = 0; i < (buffer[1] + 1); i++) {
					buffer[index] += buffer[i + 1];
				}
				index++;
				app_2d4_send(buffer, index);

				log_debug("send match code");
			}

		}
		if (timer0_taskTimer_get()->flag_1s) {
			static uint16_t cnt = 0;
			timer0_taskTimer_get()->flag_1s = 0;
			//////////////////

			cnt++;
			if (cnt == 6) {
				if (matchCode_flag == 0) {
					matchCode_flag = 1;
					app_2d4_switch_address();
				}
			}

//				log_debug("I am alive %d", cnt);

			app_work_1s_pro();

		}

//		app_uart_pro();

//////
		ucKeyCode = bsp_GetKey();
		if (ucKeyCode != KEY_NONE) {
			static uint8_t press_long_lock = 0;
			switch (ucKeyCode) {
			case KEY_UP_K1:   //ACC
				log_debug("ACC KEY up");

				break;
			case KEY_DOWN_K1:
				log_debug("relay %s", Relay_IsOn() ? "on" : "off");

				Relay_toggle();
				break;
			case KEY_LONG_K1:
				log_debug("ACC KEY down");
				break;
			case KEY_UP_K2:   //LED
				log_debug("LED KEY up");

				if (press_long_lock == 0) {
					//					g_tWork.status.bits.DEMO = 0;
					//					app_dome_start_current();
					uint8_t buffer[16] = { 0 };
					if (g_tWork.status.bits.blinkEnable) {
						uint8_t index = 0, i = 0;
						app_dome_next();
						buffer[index++] = LAMP2LCD_HEADER;
						buffer[index++] = 9;
						buffer[index++] = KEY_DOWN_CMD;
						app_dome_get_current_Name(buffer + index, 8);
						index += 8;
						for (i = 0; i < (buffer[1] + 1); i++) {
							buffer[index] += buffer[i + 1];
						}
						index++;
						app_2d4_send(buffer, index);
					}

				}
				press_long_lock = 0;
				break;
			case KEY_DOWN_K2:
				log_debug("LED KEY down");

				break;
			case KEY_LONG_K2:
				log_debug("LED KEY long");
				press_long_lock = 1;
				if (g_tWork.status.bits.blinkEnable) {
					g_tWork.status.bits.blinkEnable = 0;
					//					g_tWork.status.bits.DEMO = 0;
					app_dome_stop_current();
				} else {
					g_tWork.status.bits.blinkEnable = 1;
					g_tWork.status.bits.DEMO = 0;
					//					app_dome_start(0, 0);
					app_dome_start_current();
				}
				break;
			}
		}

	}

}

