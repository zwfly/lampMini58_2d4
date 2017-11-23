/*
 * bsp_light.c
 *
 *  Created on: 2017Äê8ÔÂ18ÈÕ
 *      Author: fly
 */

#include "bsp.h"
#include "app_dome.h"

void Light_InitHard(void) {



	Light_RGB_set(0, 0, 0);
}
static void Light_Red_set(uint16_t duty) {
	set_SFRPAGE
	;
	PWM5H = (duty >> 8) & 0xFF;
	PWM5L = duty & 0xFF;
	clr_SFRPAGE
	;
	set_LOAD;
}
static void Light_Green_set(uint16_t duty) {
	PWM3H = (duty >> 8) & 0xFF;
	PWM3L = duty & 0xFF;
	set_LOAD;
}
static void Light_Blue_set(uint16_t duty) {
	PWM0H = (duty >> 8) & 0xFF;
	PWM0L = duty & 0xFF;
	set_LOAD;
}

void Light_RGB_set(uint16_t r, uint16_t g, uint16_t b) {
	uint32_t tmp = 0;
#if 1
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
	dome_running_param.bright = br;

	if (dome_running_param.bright < 10) {
		dome_running_param.bright = 10;
	}

	Light_RGB_set(dome_running_param.color.R, dome_running_param.color.G,
			dome_running_param.color.B);
}

