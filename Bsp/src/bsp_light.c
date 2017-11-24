/*
 * bsp_light.c
 *
 *  Created on: 2017��8��18��
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
	PWM->CTL = PWM_CTL_CNTEN0_Msk | PWM_CTL_CNTMODE0_Msk;
		PWM->CTL = PWM_CTL_CNTEN1_Msk | PWM_CTL_CNTMODE1_Msk;
		PWM->CTL = PWM_CTL_CNTEN4_Msk | PWM_CTL_CNTMODE4_Msk;
	
	
	PWM_SET_PRESCALER(PWM, 0, 3);
	PWM_SET_DIVIDER(PWM, 0, PWM_CLK_DIV_1);

	PWM_SET_PRESCALER(PWM, 1, 3);
	PWM_SET_DIVIDER(PWM, 1, PWM_CLK_DIV_1);

	PWM_SET_PRESCALER(PWM, 4, 3);
	PWM_SET_DIVIDER(PWM, 4, PWM_CLK_DIV_1);

	// Set the PWM aligned type
	PWM_SET_ALIGNED_TYPE(PWM, 0, PWM_CENTER_ALIGNED);
	PWM_SET_ALIGNED_TYPE(PWM, 1, PWM_CENTER_ALIGNED);
	PWM_SET_ALIGNED_TYPE(PWM, 4, PWM_CENTER_ALIGNED);

	// Enable PWM channel 0 output
	PWM_EnableOutput(PWM, BIT0);
	PWM_EnableOutput(PWM, BIT1);
	PWM_EnableOutput(PWM, BIT4);
	// Start
	PWM_Start(PWM, BIT0);
	PWM_Start(PWM, BIT1);
	PWM_Start(PWM, BIT4);

	PWM_SET_CMR(PWM, 0, 1000);
	PWM_SET_CNR(PWM, 0, 0xFFFF);

	PWM_SET_CMR(PWM, 1, 20000);
	PWM_SET_CNR(PWM, 1, 0xFFFF);

	PWM_SET_CMR(PWM, 4, 50000);
	PWM_SET_CNR(PWM, 4, 0xFFFF);

//	Light_RGB_set(0, 0, 0);
}
static void Light_Red_set(uint16_t duty) {
PWM_SET_CMR(PWM, 1, duty);
}
static void Light_Green_set(uint16_t duty) {
PWM_SET_CMR(PWM, 0, duty);
}
static void Light_Blue_set(uint16_t duty) {
PWM_SET_CMR(PWM, 4, duty);
}

void Light_RGB_set(uint16_t r, uint16_t g, uint16_t b) {
	uint32_t tmp = 0;
#if 0
	tmp = r;
	tmp *= dome_running_param.bright;
	tmp /= 100;
	Light_Red_set(tmp & 0xFFFF);

	tmp = g;
	tmp *= dome_running_param.bright;
	tmp /= 100;
	Light_Green_set(tmp & 0xFFFF);

	tmp = b;
	tmp *= dome_running_param.bright;
	tmp /= 100;
	Light_Blue_set(tmp & 0xFFFF);
#else
	Light_Red_set(0xFFFF);
	Light_Green_set(0xFFFF);
	Light_Blue_set(0xFFFF);
#endif
}
void Light_bright_set(uint8_t br) {
//	uint16_t tmp = 0;
#if 0
	dome_running_param.bright = br;

	if (dome_running_param.bright < 10) {
		dome_running_param.bright = 10;
	}

	Light_RGB_set(dome_running_param.color.R, dome_running_param.color.G,
			dome_running_param.color.B);
#endif
}

