#ifndef _BSP_USART_FIFO_H_
#define _BSP_USART_FIFO_H_

#define	UART0_FIFO_EN	1
#define	UART1_FIFO_EN	1

///* RS485оƬ����ʹ��GPIO, PB2 */
//#define RCC_RS485_TXEN 	 RCC_APB2Periph_GPIOB
//#define PORT_RS485_TXEN  GPIOB
//#define PIN_RS485_TXEN	 GPIO_Pin_2

//#define RS485_RX_EN()	PORT_RS485_TXEN->BRR = PIN_RS485_TXEN
//#define RS485_TX_EN()	PORT_RS485_TXEN->BSRR = PIN_RS485_TXEN

/* ����˿ں� */
typedef enum {
	COM0 = 0, COM1 = 1,
} COM_PORT_E;


#if UART0_FIFO_EN == 1
#define UART0_BAUD			115200
#define UART0_TX_BUF_SIZE	1*64
#define UART0_RX_BUF_SIZE	1*64
#endif

#if UART1_FIFO_EN == 1
#define UART1_BAUD			115200
#define UART1_TX_BUF_SIZE	1*256
#define UART1_RX_BUF_SIZE	1*256
#endif

/* �����豸�ṹ�� */
typedef struct {
	UART_T *uart; /* STM32�ڲ������豸ָ�� */
	uint8_t *pTxBuf; /* ���ͻ����� */
	uint8_t *pRxBuf; /* ���ջ����� */
	uint16_t usTxBufSize; /* ���ͻ�������С */
	uint16_t usRxBufSize; /* ���ջ�������С */
	__IO uint16_t usTxWrite; /* ���ͻ�����дָ�� */
	__IO uint16_t usTxRead; /* ���ͻ�������ָ�� */
	__IO uint16_t usTxCount; /* �ȴ����͵����ݸ��� */

	__IO uint16_t usRxWrite; /* ���ջ�����дָ�� */
	__IO uint16_t usRxRead; /* ���ջ�������ָ�� */
	__IO uint16_t usRxCount; /* ��δ��ȡ�������ݸ��� */

	void (*SendBefor)(void); /* ��ʼ����֮ǰ�Ļص�����ָ�루��Ҫ����RS485�л�������ģʽ�� */
	void (*SendOver)(void); /* ������ϵĻص�����ָ�루��Ҫ����RS485������ģʽ�л�Ϊ����ģʽ�� */
	void (*ReciveNew)(uint8_t _byte); /* �����յ����ݵĻص�����ָ�� */
} UART_T_M;

void bsp_InitUart(void);
void comSendBuf(COM_PORT_E _ucPort, uint8_t *_ucaBuf, uint16_t _usLen);
void comSendChar(COM_PORT_E _ucPort, uint8_t _ucByte);
uint8_t comGetChar(COM_PORT_E _ucPort, uint8_t *_pByte);

void comClearTxFifo(COM_PORT_E _ucPort);
void comClearRxFifo(COM_PORT_E _ucPort);

//void RS485_SendBuf(uint8_t *_ucaBuf, uint16_t _usLen);
//void RS485_SendStr(char *_pBuf);

//void bsp_Set485Baud(uint32_t _baud);

void bsp_SetUart1Baud(uint32_t _baud);
void bsp_SetUart2Baud(uint32_t _baud);

#endif

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
