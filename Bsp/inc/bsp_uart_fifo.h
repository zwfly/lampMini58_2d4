#ifndef _BSP_USART_FIFO_H_
#define _BSP_USART_FIFO_H_

#define	UART0_FIFO_EN	1
#define	UART1_FIFO_EN	1

///* RS485芯片发送使能GPIO, PB2 */
//#define RCC_RS485_TXEN 	 RCC_APB2Periph_GPIOB
//#define PORT_RS485_TXEN  GPIOB
//#define PIN_RS485_TXEN	 GPIO_Pin_2

//#define RS485_RX_EN()	PORT_RS485_TXEN->BRR = PIN_RS485_TXEN
//#define RS485_TX_EN()	PORT_RS485_TXEN->BSRR = PIN_RS485_TXEN

/* 定义端口号 */
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

/* 串口设备结构体 */
typedef struct {
	UART_T *uart; /* STM32内部串口设备指针 */
	uint8_t *pTxBuf; /* 发送缓冲区 */
	uint8_t *pRxBuf; /* 接收缓冲区 */
	uint16_t usTxBufSize; /* 发送缓冲区大小 */
	uint16_t usRxBufSize; /* 接收缓冲区大小 */
	__IO uint16_t usTxWrite; /* 发送缓冲区写指针 */
	__IO uint16_t usTxRead; /* 发送缓冲区读指针 */
	__IO uint16_t usTxCount; /* 等待发送的数据个数 */

	__IO uint16_t usRxWrite; /* 接收缓冲区写指针 */
	__IO uint16_t usRxRead; /* 接收缓冲区读指针 */
	__IO uint16_t usRxCount; /* 还未读取的新数据个数 */

	void (*SendBefor)(void); /* 开始发送之前的回调函数指针（主要用于RS485切换到发送模式） */
	void (*SendOver)(void); /* 发送完毕的回调函数指针（主要用于RS485将发送模式切换为接收模式） */
	void (*ReciveNew)(uint8_t _byte); /* 串口收到数据的回调函数指针 */
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

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
