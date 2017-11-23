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
#include <stdio.h>
#include "Mini58Series.h"
#include "GPIO.h"

/**
 * @brief       Port0/Port1 IRQ
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The Port0/Port1 default IRQ, declared in startup_Mini58.s.
 */
void GPIO01_IRQHandler(void)
{
    /* To check if P1.5 interrupt occurred */
    if (P1->INTSRC & BIT5) {
        P1->INTSRC = BIT5;
        P30 = P30 ^ 1;
        printf("P1.5 INT occurred. \r\n");

    } else {
        /* Un-expected interrupt. Just clear all PORT0, PORT1 interrupts */
        P0->INTSRC = P0->INTSRC;
        P1->INTSRC = P1->INTSRC;
        printf("Un-expected interrupts. \r\n");
    }
}


/**
 * @brief       Port2/Port3/Port4 IRQ
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The Port2/Port3/Port4 default IRQ, declared in startup_Mini58.s.
 */
void GPIO234_IRQHandler(void)
{
    /* To check if P2.2 interrupt occurred */
    if (P2->INTSRC & BIT2) {
        P2->INTSRC = BIT2;
        P30 = P30 ^ 1;
        printf("P2.2 INT occurred. \r\n");
    } else {
        /* Un-expected interrupt. Just clear all PORT2, PORT3 and PORT4 interrupts */
        P2->INTSRC = P2->INTSRC;
        P3->INTSRC = P3->INTSRC;
        P4->INTSRC = P4->INTSRC;
        printf("Un-expected interrupts. \r\n");
    }
}


/**
 * @brief       External INT0 IRQ
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The External INT0(P3.2) default IRQ, declared in startup_Mini58.s.
 */
void EINT0_IRQHandler(void)
{
    /* For P3.2, clear the INT flag */
    P3->INTSRC = BIT2;
    P30 = P30 ^ 1;
    printf("P3.2 EINT0 occurred. \r\n");
}


/**
 * @brief       External INT1 IRQ
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The External INT1(P5.2) default IRQ, declared in startup_Mini58.s.
 */
void EINT1_IRQHandler(void)
{
    /* For P5.2, clear the INT flag */
    P5->INTSRC = BIT2;
    P30 = P30 ^ 1;
    printf("P5.2 EINT1 occurred. \r\n");
}

void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

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

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE,CLK_CLKSEL1_UARTSEL_XTAL,CLK_CLKDIV_UART(1));

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set P1 multi-function pins for UART RXD, TXD */
    SYS->P1_MFP = SYS_MFP_P12_UART0_RXD | SYS_MFP_P13_UART0_TXD;

    /* Set P3 multi-function pins for Clock Output */
    SYS->P3_MFP = SYS_MFP_P36_CLKO;

    /* To update the variable SystemCoreClock */
    SystemCoreClockUpdate();

    /* Lock protected registers */
    SYS_LockReg();
}

void UART_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset IP */
    SYS_ResetModule(SYS_IPRST1_UART0RST_Msk);

    /* Configure UART and set UART Baudrate */
    UART_Open(UART0, 115200);

}

/*---------------------------------------------------------------------------------------------------------*/
/* MAIN function                                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
int main (void)
{
    int32_t i32Err;

    /* Init System, IP clock and multi-function I/O */
    SYS_Init(); //In the end of SYS_Init() will issue SYS_LockReg() to lock protected register. If user want to write protected register, please issue SYS_UnlockReg() to unlock protected register.

    /* Init UART for printf */
    UART_Init();

    printf("\r\n\r\nCPU @ %dHz\r\n", SystemCoreClock);

    printf("+-------------------------------------+ \r\n");
    printf("|    Mini58 GPIO Driver Sample Code  | \r\n");
    printf("+-------------------------------------+ \r\n");

    /*-----------------------------------------------------------------------------------------------------*/
    /* GPIO Basic Mode Test --- Use Pin Data Input/Output to control GPIO pin                              */
    /*-----------------------------------------------------------------------------------------------------*/
    printf("  >> Please connect P1.0 and P3.4 first << \r\n");
    printf("     Press any key to start test by using [Pin Data Input/Output Control] \r\n\r\n");
    getchar();

    /* Configure P1.0 as Output mode and P3.4 as Input mode then close it */
    GPIO_SetMode(P1, BIT0, GPIO_MODE_OUTPUT);
    GPIO_SetMode(P3, BIT4, GPIO_MODE_INPUT);

    i32Err = 0;
    printf("  GPIO Output/Input test ...... \r\n");

    /* Use Pin Data Input/Output Control to pull specified I/O or get I/O pin status */
    P10 = 0;
    if (P34 != 0) {
        i32Err = 1;
    }

    P10 = 1;
    if (P34 != 1) {
        i32Err = 1;
    }

    if ( i32Err ) {
        printf("  [FAIL] --- Please make sure P1.0 and P3.4 are connected. \r\n");
    } else {
        printf("  [OK] \r\n");
    }

    /* Configure P1.0 and P3.4 to default Quasi-bidirectional mode */
    GPIO_SetMode(P1, BIT0, GPIO_MODE_QUASI);
    GPIO_SetMode(P3, BIT4, GPIO_MODE_QUASI);


    /*-----------------------------------------------------------------------------------------------------*/
    /* GPIO Interrupt Function Test                                                                        */
    /*-----------------------------------------------------------------------------------------------------*/
    printf("\r\n  P15, P22, P32(INT0) and P52(INT1) are used to test interrupt\r\n  and control LEDs(P30)\r\n");

    /*Configure P30 for LED control */
    GPIO_SetMode(P3, BIT0, GPIO_MODE_OUTPUT);

    /* Configure P1.5 as Input mode and enable interrupt by rising edge trigger */
    GPIO_SetMode(P1, BIT5, GPIO_MODE_INPUT);
    GPIO_EnableInt(P1, 5, GPIO_INT_RISING);
    NVIC_EnableIRQ(GPIO01_IRQn);


    /*  Configure P2.2 as Quasi-bidirection mode and enable interrupt by falling edge trigger */
    GPIO_SetMode(P2, BIT2, GPIO_MODE_QUASI);
    GPIO_EnableInt(P2, 2, GPIO_INT_FALLING);
    NVIC_EnableIRQ(GPIO234_IRQn);

    /* Configure P3.2 as EINT0 pin and enable interrupt by falling edge trigger */
    GPIO_SetMode(P3, BIT2, GPIO_MODE_INPUT);
    GPIO_EnableEINT0(P3, 2, GPIO_INT_FALLING);
    NVIC_EnableIRQ(EINT0_IRQn);

    /* Configure P5.2 as EINT1 pin and enable interrupt by rising and falling edge trigger */
    GPIO_SetMode(P5, BIT2, GPIO_MODE_INPUT);
    GPIO_EnableEINT1(P5, 2, GPIO_INT_BOTH_EDGE);
    NVIC_EnableIRQ(EINT1_IRQn);

    /* Enable interrupt de-bounce function and select de-bounce sampling cycle time */
    GPIO_SET_DEBOUNCE_TIME(GPIO_DBCTL_DBCLKSRC_HCLK, GPIO_DBCTL_DBCLKSEL_1);
    GPIO_ENABLE_DEBOUNCE(P1, BIT5);
    GPIO_ENABLE_DEBOUNCE(P2, BIT2);
    GPIO_ENABLE_DEBOUNCE(P3, BIT2);
    GPIO_ENABLE_DEBOUNCE(P5, BIT2);

    /* Waiting for interrupts */
    while (1);

}


