/*************************************************************************
* STM32 USART LIBRARY (SPL WRAPPER)
*
* MARCH 25 2017
* ANKIT BHATNAGAR
* ANKIT.BHATNAGARINDIA@GMAIL.COM
*
* NOTE: IN STM32, USART PROVIDES A SYNCHORNOUS MODE (WITH CLOCK SIGNAL)
* THAT WORKS LIKE SPI. IT SUPPORTS DATA LENGTH OF 8 AND 9 BITS. HOWEVER
* IT ONLY PROVIDES LSB FIRST TRANSFER
*
* THIS LIBRARY PROVIDES OPTION TO REVERSE THE DATA BEFORE SENDING IN SYNCHRONOUS
* MODE THIS EMULATING MSB FIRST TRANSFER
*
* DOES NOT SYUPPORT HARDWARE FLOW CONTROL
*
* SYANCRONOUS MODE MAX : 4.5MHZ (HSE, SYSCLK @ 72mhz) 4MHZ(HSI, SYSCLK @ 64MHZ)
* 
* REFERENCES
*		(1) www.edn.com/electronics-blogs/embedded-basics/4440395/USART-vs-UART--Know-the-difference
*		(2) http://forum.micromouseonline.com/index.php?topic=460.0
* ***********************************************************************/


#ifndef _ARM_STM32_USART_
#define _ARM_STM32_USART_

#include <stdint.h>
//CHECK WHAT MCU US BEING USED IN ORDER TO INCLUDE
//THE RIGHT FILE FROM STM SPL
//THE MCU SHOULD BE DEFINED IN TARGET OPTIONS -> C/C++
#ifdef STM32F103
	#include "stm32f10x.h"
	#include "stm32f10x_usart.h"
	#include "stm32f10x_gpio.h"
	
	#define ARM_STM32_USART_PERIPHERAL_USART1	1
	#define ARM_STM32_USART_PERIPHERAL_USART2	2
	
	#define ARM_STM32_USART_GPIO_SPEED_2MHZ 	2
	#define ARM_STM32_USART_GPIO_SPEED_10MHZ 	1
	#define ARM_STM32_USART_GPIO_SPEED_50MHZ	3
	
	#define ARM_STM32_USART_PERIPHERAL_MODE_RX		USART_Mode_Rx
	#define ARM_STM32_USART_PERIPHERAL_MODE_TX		USART_Mode_Tx
	#define ARM_STM32_USART_PERIPHERAL_MODE_RX_TX	(ARM_STM32_USART_PERIPHERAL_MODE_RX | ARM_STM32_USART_PERIPHERAL_MODE_TX)
	
	#define ARM_STM32_USART_PERIPHERAL_HF_NONE		USART_HardwareFlowControl_None
	#define ARM_STM32_USART_PERIPHERAL_HF_RTS			USART_HardwareFlowControl_RTS
	#define ARM_STM32_USART_PERIPHERAL_HF_CTS			USART_HardwareFlowControl_CTS
	#define ARM_STM32_USART_PERIPHERAL_HF_RTS_CTS	USART_HardwareFlowControl_RTS_CTS
	
	#define ARM_STM32_USART_PERIPHERAL_PARITY_NONE	USART_Parity_No
	#define ARM_STM32_USART_PERIPHERAL_PARITY_EVEN	USART_Parity_Even
	#define ARM_STM32_USART_PERIPHERAL_PARITY_ODD		USART_Parity_Odd
	
	#define ARM_STM32_USART_PERIPHERAL_STOPBITS_1		USART_StopBits_1
	#define ARM_STM32_USART_PERIPHERAL_STOPBITS_0_5	USART_StopBits_0_5
	#define ARM_STM32_USART_PERIPHERAL_STOPBITS_2		USART_StopBits_2
	#define ARM_STM32_USART_PERIPHERAL_STOPBITS_1_5	USART_StopBits_1_5
	
	#define ARM_STM32_USART_PERIPHERAL_WORDLEN_8	USART_WordLength_8b
	#define ARM_STM32_USART_PERIPHERAL_WORDLEN_9	USART_WordLength_9b
	
	#define ARM_STM32_USART_PERIPHERAL_CLOCK_ENABLE		USART_Clock_Enable
	#define ARM_STM32_USART_PERIPHERAL_CLOCK_DISABLE	USART_Clock_Disable
	
	#define ARM_STM32_USART_PERIPHERAL_CLOCK_CPOL_LOW		USART_CPOL_Low
	#define ARM_STM32_USART_PERIPHERAL_CLOCK_CPOL_HIGH	USART_CPOL_High
	
	#define ARM_STM32_USART_PERIPHERAL_CLOCK_CPHA_1EDGE	USART_CPHA_1Edge
	#define ARM_STM32_USART_PERIPHERAL_CLOCK_CPHA_2EDGE	USART_CPHA_2Edge
	
	#define ARM_STM32_USART_PERIPHERAL_CLOCK_LASTBIT_ENABLE		USART_LastBit_Enable
	#define ARM_STM32_USART_PERIPHERAL_CLOCK_LASTBIT_DISABLE	USART_LastBit_Disable
#endif

#ifdef STM32F072

#endif


void ARM_STM32_USART_Init_Pins(uint8_t usart_num, uint8_t usart_gpio_speed);
void ARM_STM32_USART_Set_Parameters(uint8_t usart_num, uint16_t usart_mode, uint16_t usart_flow, uint16_t usart_parity, uint16_t usart_stopbits, uint16_t word_len, uint32_t usart_baudrate);
void ARM_STM32_USART_Set_Synchronous_Clock(uint8_t usart_num, uint16_t usart_clk, uint16_t usart_cpha, uint16_t usart_cpol, uint16_t usart_lastbit);

void ARM_STM32_USART_Start(uint8_t usart_num);
void ARM_STM32_USART_Stop(uint8_t usart_num);

void ARM_STM32_USART_Send_Char(uint8_t usart_num, uint16_t data);
void ARM_STM32_USART_Send_String(uint8_t usart_num, uint16_t* str, uint8_t len);
void ARM_STM32_USART_Send_Char_Reversed(uint8_t usart_num, uint16_t data, uint8_t bit_len);
void ARM_STM32_USART_Send_String_Reversed(uint8_t usart_num, uint16_t* str, uint8_t len, uint8_t bit_len);
uint16_t ARM_STM32_USART_Get_Char(uint8_t usart_num);
uint16_t ARM_STM32_USART_Send_Get_Data(uint8_t spi_num, uint16_t data);

void ARM_STM32_USART_Deinit(uint8_t usart_num);

#endif


