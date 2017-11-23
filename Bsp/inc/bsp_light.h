/*
 * bsp_light.h
 *
 *  Created on: 2017Äê8ÔÂ18ÈÕ
 *      Author: fly
 */

#ifndef BSP_INC_BSP_LIGHT_H_
#define BSP_INC_BSP_LIGHT_H_

void Light_InitHard(void);
//void Light_Red_set(uint16_t duty);
//void Light_Green_set(uint16_t duty);
//void Light_Blue_set(uint16_t duty);
void Light_RGB_set(uint16_t r, uint16_t g, uint16_t b);
void Light_bright_set(uint8_t br);

#endif /* BSP_INC_BSP_LIGHT_H_ */
