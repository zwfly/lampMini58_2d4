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

	/* Enable HIRC clock (Internal RC 22.1184MHz) */
	CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);

	/* Wait for HIRC clock ready */
	CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

	/* Select HCLK clock source as HIRC and and HCLK source divider as 1 */
	CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV_HCLK(1));

	/* Set core clock as PLL_CLOCK from PLL */
	CLK_SetCoreClock(PLL_CLOCK);

#endif

	/* To update the variable SystemCoreClock */
	SystemCoreClockUpdate();

	/* Lock protected registers */
	SYS_LockReg();
}

/*---------------------------------------------------------------------------------------------------------*/
/* MAIN function                                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
int main(void) {
	uint8_t ucKeyCode;
//	int32_t i32Err;

	/* Init System */
	SYS_Init();

	bsp_Init();

#if 1
	LITE_openlog("lamp");
	LITE_set_loglevel(LOG_DEBUG_LEVEL);
#else
	LITE_closelog();
#endif

	log_debug(" CPU @ %dHz\r\n", SystemCoreClock);

	printf("+-------------------------------------+ \r\n");
	printf("+-------------------------------------+ \r\n");

	while (1) {

		ucKeyCode = bsp_GetKey();
		if (ucKeyCode != KEY_NONE) {
			switch (ucKeyCode) {
			case KEY_UP_K1:   //
				break;
			case KEY_DOWN_K1: {


			}
				break;
			case KEY_LONG_K1:
				break;
			case KEY_UP_K2:   //
				break;
			case KEY_DOWN_K2:

//				Relay_toggle();
				break;
			case KEY_LONG_K2:
				break;
			}
		}

	}

}

