/*
 * bsp_timer0.c
 *
 *  Created on: 2017Äê6ÔÂ28ÈÕ
 *      Author: fly
 */

#include "bsp.h"
#include "app_dome.h"
#include "string.h"

static Task_time taskTime;

static void timer0_ParamInit(void);
void Timer0_InitHard(void) {

	timer0_ParamInit();

	SYS_ResetModule(TMR0_RST);

	/* Enable IP clock */
	CLK_EnableModuleClock(TMR0_MODULE);

	/* Select IP clock source */
	CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HIRC, 0);

	// Set timer 0 working 1Hz in periodic mode
	TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 1000);

	// Enable timer interrupt
	TIMER_EnableInt(TIMER0);
	NVIC_EnableIRQ(TMR0_IRQn);

	// Start Timer 0
	TIMER_Start(TIMER0);
}

Task_time* timer0_taskTimer_get(void) {
	return &taskTime;
}

static void timer0_ParamInit(void) {

	memset((uint8_t *) &taskTime, 0, sizeof(Task_time));

}

void TMR0_IRQHandler(void) {

	taskTime.flag_1ms = 1;

	if (++taskTime.cnt_10ms >= 10) {
		taskTime.cnt_10ms = 0;
		taskTime.flag_10ms = 1;
	}
	if (++taskTime.cnt_100ms >= 100) {
		taskTime.cnt_100ms = 0;
		taskTime.flag_100ms = 1;

	}
	if (++taskTime.cnt_500ms >= 500) {
		taskTime.cnt_500ms = 0;
		taskTime.flag_500ms = 1;
	}

	if (++taskTime.cnt_1s >= 1000) {
		taskTime.cnt_1s = 0;
		taskTime.flag_1s = 1;

	}

	// clear timer interrupt flag
	TIMER_ClearIntFlag(TIMER0);
}

