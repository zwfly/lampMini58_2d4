#ifndef _BSP_H_
#define _BSP_H

#include <stdio.h>
#include <stdint.h>
#include "Mini58Series.h"
#include "gpio.h"
#include "clk.h"
#include "sys.h"
#include "uart.h"
#include "timer.h"
#include "pwm.h"
#include "fmc.h"

#include "bsp_2d4.h"
#include "bsp_uart.h"
#include "bsp_timer0.h"
#include "bsp_light.h"
#include "bsp_relay.h"
#include "bsp_eeprom.h"
#include "bsp_key.h"


void bsp_Init(void);

#endif

/***************************** (END OF FILE) *********************************/
