#include "bsp.h"


#if UART0_FIFO_EN == 1
static UART_T_M g_tUart0;
static uint8_t g_TxBuf0[UART0_TX_BUF_SIZE]; /* ���ͻ����� */
static uint8_t g_RxBuf0[UART0_RX_BUF_SIZE]; /* ���ջ����� */
#endif

#if UART1_FIFO_EN == 1
static UART_T_M g_tUart1;
static uint8_t g_TxBuf1[UART1_TX_BUF_SIZE]; /* ���ͻ����� */
static uint8_t g_RxBuf1[UART1_RX_BUF_SIZE]; /* ���ջ����� */
#endif

static void UartVarInit(void);
static void InitHardUart(void);
static void UartSend(UART_T_M *_pUart, uint8_t *_ucaBuf, uint16_t _usLen);
static uint8_t UartGetChar(UART_T_M *_pUart, uint8_t *_pByte);
static void UartIRQ(UART_T_M *_pUart);
static void ConfigUartNVIC(void);

//void RS485_InitTXE(void);

/*
 *********************************************************************************************************
 *	�� �� ��: bsp_InitUart
 *	����˵��: ��ʼ������Ӳ��������ȫ�ֱ�������ֵ.
 *	��    ��:  ��
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
void bsp_InitUart(void) {
	UartVarInit(); /* �����ȳ�ʼ��ȫ�ֱ���,������Ӳ�� */

	InitHardUart(); /* ���ô��ڵ�Ӳ������(�����ʵ�) */

	ConfigUartNVIC(); /* ���ô����ж� */
}

/*
 *********************************************************************************************************
 *	�� �� ��: ComToUart
 *	����˵��: ��COM�˿ں�ת��ΪUARTָ��
 *	��    ��: _ucPort: �˿ں�(COM1 - COM6)
 *	�� �� ֵ: uartָ��
 *********************************************************************************************************
 */
UART_T_M *ComToUart(COM_PORT_E _ucPort) {
	if (_ucPort == COM0) {
#if UART0_FIFO_EN == 1
		return &g_tUart0;
#else
		return 0;
#endif
	} else if (_ucPort == COM1) {
#if UART1_FIFO_EN == 1
		return &g_tUart1;
#else
		return 0;
#endif
	} else {
		/* �����κδ��� */
		return 0;
	}
}

/*
 *********************************************************************************************************
 *	�� �� ��: comSendBuf
 *	����˵��: �򴮿ڷ���һ�����ݡ����ݷŵ����ͻ��������������أ����жϷ�������ں�̨��ɷ���
 *	��    ��: _ucPort: �˿ں�(COM1 - COM6)
 *			  _ucaBuf: �����͵����ݻ�����
 *			  _usLen : ���ݳ���
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
void comSendBuf(COM_PORT_E _ucPort, uint8_t *_ucaBuf, uint16_t _usLen) {
	UART_T_M *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0) {
		return;
	}

	if (pUart->SendBefor != 0) {
		pUart->SendBefor(); /* �����RS485ͨ�ţ���������������н�RS485����Ϊ����ģʽ */
	}

	UartSend(pUart, _ucaBuf, _usLen);
}

/*
 *********************************************************************************************************
 *	�� �� ��: comSendChar
 *	����˵��: �򴮿ڷ���1���ֽڡ����ݷŵ����ͻ��������������أ����жϷ�������ں�̨��ɷ���
 *	��    ��: _ucPort: �˿ں�(COM1 - COM6)
 *			  _ucByte: �����͵�����
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
void comSendChar(COM_PORT_E _ucPort, uint8_t _ucByte) {
	comSendBuf(_ucPort, &_ucByte, 1);
}

/*
 *********************************************************************************************************
 *	�� �� ��: comGetChar
 *	����˵��: �Ӵ��ڻ�������ȡ1�ֽڣ��������������������ݾ���������
 *	��    ��: _ucPort: �˿ں�(COM1 - COM6)
 *			  _pByte: ���յ������ݴ���������ַ
 *	�� �� ֵ: 0 ��ʾ������, 1 ��ʾ��ȡ����Ч�ֽ�
 *********************************************************************************************************
 */
uint8_t comGetChar(COM_PORT_E _ucPort, uint8_t *_pByte) {
	UART_T_M *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0) {
		return 0;
	}

	return UartGetChar(pUart, _pByte);
}

/*
 *********************************************************************************************************
 *	�� �� ��: comClearTxFifo
 *	����˵��: ���㴮�ڷ��ͻ�����
 *	��    ��: _ucPort: �˿ں�(COM1 - COM6)
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
void comClearTxFifo(COM_PORT_E _ucPort) {
	UART_T_M *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0) {
		return;
	}

	pUart->usTxWrite = 0;
	pUart->usTxRead = 0;
	pUart->usTxCount = 0;
}

/*
 *********************************************************************************************************
 *	�� �� ��: comClearRxFifo
 *	����˵��: ���㴮�ڽ��ջ�����
 *	��    ��: _ucPort: �˿ں�(COM1 - COM6)
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
void comClearRxFifo(COM_PORT_E _ucPort) {
	UART_T_M *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0) {
		return;
	}

	pUart->usRxWrite = 0;
	pUart->usRxRead = 0;
	pUart->usRxCount = 0;
}

/*
 *********************************************************************************************************
 *	�� �� ��: UartVarInit
 *	����˵��: ��ʼ��������صı���
 *	��    ��: ��
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
static void UartVarInit(void) {
#if UART0_FIFO_EN == 1
	g_tUart0.uart = UART0; /* STM32 �����豸 */
	g_tUart0.pTxBuf = g_TxBuf0; /* ���ͻ�����ָ�� */
	g_tUart0.pRxBuf = g_RxBuf0; /* ���ջ�����ָ�� */
	g_tUart0.usTxBufSize = UART0_TX_BUF_SIZE; /* ���ͻ�������С */
	g_tUart0.usRxBufSize = UART0_RX_BUF_SIZE; /* ���ջ�������С */
	g_tUart0.usTxWrite = 0; /* ����FIFOд���� */
	g_tUart0.usTxRead = 0; /* ����FIFO������ */
	g_tUart0.usRxWrite = 0; /* ����FIFOд���� */
	g_tUart0.usRxRead = 0; /* ����FIFO������ */
	g_tUart0.usRxCount = 0; /* ���յ��������ݸ��� */
	g_tUart0.usTxCount = 0; /* �����͵����ݸ��� */
	g_tUart0.SendBefor = 0; /* ��������ǰ�Ļص����� */
	g_tUart0.SendOver = 0; /* ������Ϻ�Ļص����� */
	g_tUart0.ReciveNew = 0; /* ���յ������ݺ�Ļص����� */
#endif

#if UART1_FIFO_EN == 1
	g_tUart1.uart = UART1; /* STM32 �����豸 */
	g_tUart1.pTxBuf = g_TxBuf1; /* ���ͻ�����ָ�� */
	g_tUart1.pRxBuf = g_RxBuf1; /* ���ջ�����ָ�� */
	g_tUart1.usTxBufSize = UART1_TX_BUF_SIZE; /* ���ͻ�������С */
	g_tUart1.usRxBufSize = UART1_RX_BUF_SIZE; /* ���ջ�������С */
	g_tUart1.usTxWrite = 0; /* ����FIFOд���� */
	g_tUart1.usTxRead = 0; /* ����FIFO������ */
	g_tUart1.usRxWrite = 0; /* ����FIFOд���� */
	g_tUart1.usRxRead = 0; /* ����FIFO������ */
	g_tUart1.usRxCount = 0; /* ���յ��������ݸ��� */
	g_tUart1.usTxCount = 0; /* �����͵����ݸ��� */
	g_tUart1.SendBefor = 0; /* ��������ǰ�Ļص����� */
	g_tUart1.SendOver = 0; /* ������Ϻ�Ļص����� */
	g_tUart1.ReciveNew = 0; /* ���յ������ݺ�Ļص����� */
#endif

}

/*
 *********************************************************************************************************
 *	�� �� ��: InitHardUart
 *	����˵��: ���ô��ڵ�Ӳ�������������ʣ�����λ��ֹͣλ����ʼλ��У��λ���ж�ʹ�ܣ��ʺ���STM32-F4������
 *	��    ��: ��
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
static void InitHardUart(void) {

#if UART0_FIFO_EN == 1		/* ����1 TX = PA9   RX = PA10 �� TX = PB6   RX = PB7*/

	/* Enable IP clock */
	CLK_EnableModuleClock(UART0_MODULE);

	/* Select IP clock source */
	CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UARTSEL_HIRC,
			CLK_CLKDIV_UART(1));

	/*---------------------------------------------------------------------------------------------------------*/
	/* Init I/O Multi-function                                                                                 */
	/*---------------------------------------------------------------------------------------------------------*/
	/* Set P1 multi-function pins for UART RXD, TXD */
	SYS->P5_MFP = SYS_MFP_P51_UART0_RXD | SYS_MFP_P50_UART0_TXD;

	/* Reset IP */
	SYS_ResetModule(SYS_IPRST1_UART0RST_Msk);

	/* Configure UART and set UART Baudrate */
	UART_Open(UART0, UART0_BAUD);

#endif

#if UART1_FIFO_EN == 1		/* ����1 TX = PA9   RX = PA10 �� TX = PB6   RX = PB7*/

	/* Enable IP clock */
	CLK_EnableModuleClock(UART1_MODULE);

	/* Select IP clock source */
	CLK_SetModuleClock(UART1_MODULE, CLK_CLKSEL1_UARTSEL_HIRC,
			CLK_CLKDIV_UART(1));

	/*---------------------------------------------------------------------------------------------------------*/
	/* Init I/O Multi-function                                                                                 */
	/*---------------------------------------------------------------------------------------------------------*/
	/* Set P1 multi-function pins for UART RXD, TXD */
	SYS->P2_MFP = SYS_MFP_P24_UART1_RXD | SYS_MFP_P25_UART1_TXD;

	/* Reset IP */
	SYS_ResetModule(SYS_IPRST1_UART1RST_Msk);

	/* Configure UART and set UART Baudrate */
	UART_Open(UART1, UART1_BAUD);

#endif

}

/*
 *********************************************************************************************************
 *	�� �� ��: ConfigUartNVIC
 *	����˵��: ���ô���Ӳ���ж�.
 *	��    ��:  ��
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
static void ConfigUartNVIC(void) {

#if UART0_FIFO_EN == 1

#endif

#if UART1_FIFO_EN == 1

	/* Enable Interrupt and install the call back function */
//	UART_ENABLE_INT(UART1, (UART_INTEN_RDAIEN_Msk | UART_INTEN_THREIEN_Msk | UART_INTEN_RXTOIEN_Msk));
	UART_ENABLE_INT(UART1, (UART_INTEN_RDAIEN_Msk | UART_INTEN_THREIEN_Msk));
	NVIC_EnableIRQ(UART1_IRQn);

#endif

}

/*
 *********************************************************************************************************
 *	�� �� ��: UartSend
 *	����˵��: ��д���ݵ�UART���ͻ�����,�����������жϡ��жϴ�����������Ϻ��Զ��رշ����ж�
 *	��    ��:  ��
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
static void UartSend(UART_T_M *_pUart, uint8_t *_ucaBuf, uint16_t _usLen) {
	uint16_t i;
	for (i = 0; i < _usLen; i++) {
		/* ������ͻ������Ѿ����ˣ���ȴ��������� */
#if 0
		/*
		 �ڵ���GPRS����ʱ������Ĵ������������while ��ѭ��
		 ԭ�� ���͵�1���ֽ�ʱ _pUart->usTxWrite = 1��_pUart->usTxRead = 0;
		 ������while(1) �޷��˳�
		 */
		while (1)
		{
			uint16_t usRead;

			DISABLE_INT();
			usRead = _pUart->usTxRead;
			ENABLE_INT();

			if (++usRead >= _pUart->usTxBufSize)
			{
				usRead = 0;
			}

			if (usRead != _pUart->usTxWrite)
			{
				break;
			}
		}
#else
		/* �� _pUart->usTxBufSize == 1 ʱ, ����ĺ���������(������) */
		while (1) {
			__IO uint16_t usCount;

			DISABLE_INT();
			usCount = _pUart->usTxCount;
			ENABLE_INT();

			if (usCount < _pUart->usTxBufSize) {
				break;
			}
		}
#endif

		/* �����������뷢�ͻ����� */
		_pUart->pTxBuf[_pUart->usTxWrite] = _ucaBuf[i];

		DISABLE_INT();
		if (++_pUart->usTxWrite >= _pUart->usTxBufSize) {
			_pUart->usTxWrite = 0;
		}
		_pUart->usTxCount++;
		ENABLE_INT();
	}

	UART_EnableInt(_pUart->uart, UART_INTEN_THREIEN_Msk);

//	USART_ITConfig(_pUart->uart, USART_IT_TXE, ENABLE);
}

/*
 *********************************************************************************************************
 *	�� �� ��: UartGetChar
 *	����˵��: �Ӵ��ڽ��ջ�������ȡ1�ֽ����� ��������������ã�
 *	��    ��: _pUart : �����豸
 *			  _pByte : ��Ŷ�ȡ���ݵ�ָ��
 *	�� �� ֵ: 0 ��ʾ������  1��ʾ��ȡ������
 *********************************************************************************************************
 */
static uint8_t UartGetChar(UART_T_M *_pUart, uint8_t *_pByte) {
	uint16_t usCount;

	/* usRxWrite �������жϺ����б���д���������ȡ�ñ���ʱ����������ٽ������� */
	DISABLE_INT();
	usCount = _pUart->usRxCount;
	ENABLE_INT();

	/* �������д������ͬ���򷵻�0 */
//if (_pUart->usRxRead == usRxWrite)
	if (usCount == 0) /* �Ѿ�û������ */
	{
		return 0;
	} else {
		*_pByte = _pUart->pRxBuf[_pUart->usRxRead]; /* �Ӵ��ڽ���FIFOȡ1������ */

		/* ��дFIFO������ */
		DISABLE_INT();
		if (++_pUart->usRxRead >= _pUart->usRxBufSize) {
			_pUart->usRxRead = 0;
		}
		_pUart->usRxCount--;
		ENABLE_INT();
		return 1;
	}
}

/*
 *********************************************************************************************************
 *	�� �� ��: UartIRQ
 *	����˵��: ���жϷ��������ã�ͨ�ô����жϴ�����
 *	��    ��: _pUart : �����豸
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
static void UartIRQ(UART_T_M *_pUart) {
	/* ��������ж�  */
	if (_pUart->uart->INTSTS & UART_INTSTS_RDAINT_Msk) {
		/* �Ӵ��ڽ������ݼĴ�����ȡ���ݴ�ŵ�����FIFO */
		uint8_t ch;

		/* Get all the input characters */
		while (UART_IS_RX_READY(_pUart->uart)) {
			/* Get the character from UART Buffer */
			ch = UART_READ(_pUart->uart);
			_pUart->pRxBuf[_pUart->usRxWrite] = ch;
			if (++_pUart->usRxWrite >= _pUart->usRxBufSize) {
				_pUart->usRxWrite = 0;
			}
			if (_pUart->usRxCount < _pUart->usRxBufSize) {
				_pUart->usRxCount++;
			}

			/* �ص�����,֪ͨӦ�ó����յ�������,һ���Ƿ���1����Ϣ��������һ����� */
			//if (_pUart->usRxWrite == _pUart->usRxRead)
			//if (_pUart->usRxCount == 1)
			{
				if (_pUart->ReciveNew) {
					_pUart->ReciveNew(ch);
				}
			}

		}
	}
	/* �����ͻ��������ж� */
	if (_pUart->uart->INTSTS & UART_INTSTS_THREINT_Msk) {
		//if (_pUart->usTxRead == _pUart->usTxWrite)
		if (_pUart->usTxCount == 0) {
			/* ���ͻ�������������ȡ��ʱ�� ��ֹ���ͻ��������ж� ��ע�⣺��ʱ���1�����ݻ�δ����������ϣ�*/
//			USART_ITConfig(_pUart->uart, USART_IT_TXE, DISABLE);
			UART_DisableInt(_pUart->uart, UART_INTEN_THREIEN_Msk);

			/* ʹ�����ݷ�������ж� */
//			USART_ITConfig(_pUart->uart, USART_IT_TC, ENABLE);
//			UART_DisableInt(_pUart->uart, UART_INTEN_THREIEN_Msk);
		} else {
			/* �ӷ���FIFOȡ1���ֽ�д�봮�ڷ������ݼĴ��� */
			UART_WRITE(_pUart->uart, _pUart->pTxBuf[_pUart->usTxRead]);
			if (++_pUart->usTxRead >= _pUart->usTxBufSize) {
				_pUart->usTxRead = 0;
			}
			_pUart->usTxCount--;
		}
	}
#if 0
	/* ����bitλȫ��������ϵ��ж� */
	else if (USART_GetITStatus(_pUart->uart, UART_IT_TC) != RESET) {
		//if (_pUart->usTxRead == _pUart->usTxWrite)
		if (_pUart->usTxCount == 0) {
			/* �������FIFO������ȫ��������ϣ���ֹ���ݷ�������ж� */
			USART_ITConfig(_pUart->uart, UART_IT_TC, DISABLE);

			/* �ص�����, һ����������RS485ͨ�ţ���RS485оƬ����Ϊ����ģʽ��������ռ���� */
			if (_pUart->SendOver) {
				_pUart->SendOver();
			}
		} else {
			/* ��������£��������˷�֧ */

			/* �������FIFO�����ݻ�δ��ϣ���ӷ���FIFOȡ1������д�뷢�����ݼĴ��� */
			USART_SendData(_pUart->uart, _pUart->pTxBuf[_pUart->usTxRead]);
			if (++_pUart->usTxRead >= _pUart->usTxBufSize) {
				_pUart->usTxRead = 0;
			}
			_pUart->usTxCount--;
		}
	}
#endif
}

/*
 *********************************************************************************************************
 *	�� �� ��: USART1_IRQHandler  USART2_IRQHandler USART3_IRQHandler UART4_IRQHandler UART5_IRQHandler
 *	����˵��: USART�жϷ������
 *	��    ��: ��
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */

#if UART0_FIFO_EN == 1
void USART0_IRQHandler(void) {
	UartIRQ(&g_tUart0);
}
#endif

#if UART1_FIFO_EN == 1
void USART1_IRQHandler(void)
{
	UartIRQ(&g_tUart1);
}
#endif
#if 0
/*
 *********************************************************************************************************
 *	�� �� ��: fputc
 *	����˵��: �ض���putc��������������ʹ��printf�����Ӵ���1��ӡ���
 *	��    ��: ��
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
int fputc(int ch, FILE *f) {
#if 0	/* ����Ҫprintf���ַ�ͨ�������ж�FIFO���ͳ�ȥ��printf�������������� */
	comSendChar(COM1, ch);

	return ch;
#else	/* ����������ʽ����ÿ���ַ�,�ȴ����ݷ������ */
	/* дһ���ֽڵ�USART1 */
//	UART_WRITE(UART0, (uint8_t ) ch);
	/* �ȴ����ͽ��� */
//	while (UART0->INTSTS & UART_INTSTS_THREINT_Msk) {
//	}
	while (UART0->FIFOSTS & UART_FIFOSTS_TXFULL_Msk)
	;
	UART0->DAT = ch;
	if (ch == '\n') {
		while (UART0->FIFOSTS & UART_FIFOSTS_TXFULL_Msk)
		;
		UART0->DAT = '\r';
	}

	return ch;
#endif
}

/*
 *********************************************************************************************************
 *	�� �� ��: fgetc
 *	����˵��: �ض���getc��������������ʹ��getchar�����Ӵ���1��������
 *	��    ��: ��
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
int fgetc(FILE *f) {

#if 1	/* �Ӵ��ڽ���FIFO��ȡ1������, ֻ��ȡ�����ݲŷ��� */
	uint8_t ucData;

	while (comGetChar(COM0, &ucData) == 0)
	;

	return ucData;
#else
	/* �ȴ�����1�������� */
	while (USART_GetFlagStatus(UART1, USART_FLAG_RXNE) == RESET);

	return (int)USART_ReceiveData(UART1);
#endif
}
#endif

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
