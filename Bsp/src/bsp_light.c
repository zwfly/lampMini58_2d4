/*
 * bsp_light.c
 *
 *  Created on: 2017Äê8ÔÂ18ÈÕ
 *      Author: fly
 */

#include "bsp.h"
#include "app_dome.h"

void Light_InitHard(void) {

	SYS_ResetModule(PWM0_RST);

	/* Enable IP clock */
	CLK_EnableModuleClock(PWMCH01_MODULE);
	CLK_EnableModuleClock(PWMCH45_MODULE);

	/* Select IP clock source */
	CLK_SetModuleClock(PWMCH01_MODULE, CLK_CLKSEL1_PWMCH01SEL_HCLK, 0);
	CLK_SetModuleClock(PWMCH45_MODULE, CLK_CLKSEL2_PWMCH45SEL_HCLK, 0);

	SYS->P1_MFP |= SYS_MFP_P12_PWM0_CH0 | SYS_MFP_P13_PWM0_CH1
			| SYS_MFP_P14_PWM0_CH4;

	// PWM-Timer 0 enable and Auto-reload
	PWM->CTL = PWM_CTL_CNTEN0_Msk | PWM_CTL_CNTMODE0_Msk | PWM_CTL_CNTEN1_Msk
			| PWM_CTL_CNTMODE1_Msk | PWM_CTL_CNTEN4_Msk | PWM_CTL_CNTMODE4_Msk;
//	PWM->CTL = PWM_CTL_CNTEN1_Msk | PWM_CTL_CNTMODE1_Msk;
//	PWM->CTL = PWM_CTL_CNTEN4_Msk | PWM_CTL_CNTMODE4_Msk;

	PWM_SET_PRESCALER(PWM, 0, 3);
	PWM_SET_PRESCALER(PWM, 1, 3);
	PWM_SET_PRESCALER(PWM, 4, 3);

	PWM_SET_DIVIDER(PWM, 0, PWM_CLK_DIV_1);
	PWM_SET_DIVIDER(PWM, 1, PWM_CLK_DIV_1);
	PWM_SET_DIVIDER(PWM, 4, PWM_CLK_DIV_1);

	// Set the PWM aligned type
	PWM_SET_ALIGNED_TYPE(PWM, 0, PWM_EDGE_ALIGNED);
	PWM_SET_ALIGNED_TYPE(PWM, 1, PWM_EDGE_ALIGNED);
	PWM_SET_ALIGNED_TYPE(PWM, 4, PWM_EDGE_ALIGNED); //PWM_CENTER_ALIGNED

	// Enable PWM channel 0 output
	PWM_EnableOutput(PWM, BIT0);
	PWM_EnableOutput(PWM, BIT1);
	PWM_EnableOutput(PWM, BIT4);

//	PWM_ENABLE_OUTPUT_INVERTER(PWM, BIT0);
//	PWM_ENABLE_OUTPUT_INVERTER(PWM, BIT1);
//	PWM_ENABLE_OUTPUT_INVERTER(PWM, BIT4);

// Start
	PWM_Start(PWM, BIT0);
	PWM_Start(PWM, BIT1);
	PWM_Start(PWM, BIT4);

	PWM_SET_CNR(PWM, 0, 0xFFFF);
	PWM_SET_CMR(PWM, 0, 0);

	PWM_SET_CNR(PWM, 1, 0xFFFF);
	PWM_SET_CMR(PWM, 1, 0);

	PWM_SET_CNR(PWM, 4, 0xFFFF);
	PWM_SET_CMR(PWM, 4, 0);

	///////////////
//	Light_bright_set(95);
//	Light_RGB_set(0,50000,0);
}
static void Light_Red_set(uint16_t duty) {
	PWM_SET_CMR(PWM, 0, duty);
}
static void Light_Green_set(uint16_t duty) {
	PWM_SET_CMR(PWM, 1, duty);
}
static void Light_Blue_set(uint16_t duty) {
	PWM_SET_CMR(PWM, 4, duty);
}

static uint32_t u32_tmp = 0;
void Light_RGB_set(uint16_t r, uint16_t g, uint16_t b) {
#if 1
	u32_tmp = r;
	u32_tmp = (u32_tmp * dome_running_param.bright) / 100;
	Light_Red_set(u32_tmp & 0xFFFF);
//	log_debug("red set %04X", u32_tmp);

	u32_tmp = g;
	u32_tmp = (u32_tmp * dome_running_param.bright) / 100;
	Light_Green_set(u32_tmp & 0xFFFF);
//	log_debug("green set %04X", u32_tmp);

	u32_tmp = b;
	u32_tmp = (u32_tmp * dome_running_param.bright) / 100;
	Light_Blue_set(u32_tmp & 0xFFFF);
//	log_debug("blue set %04X\r\n", u32_tmp);
#endif
}
void Light_bright_set(uint8_t br) {
//	uint16_t tmp = 0;
#if 1
	dome_running_param.bright = br;

	if (dome_running_param.bright < 10) {
		dome_running_param.bright = 10;
	}
	Light_RGB_set(dome_running_param.color.R, dome_running_param.color.G,
			dome_running_param.color.B);
#endif
}

