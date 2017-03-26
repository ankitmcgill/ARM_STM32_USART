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
#include "ARM_STM32_USART.h"

void ARM_STM32_USART_Init_Pins(uint8_t usart_num, uint8_t usart_gpio_speed)
{
	//INITIALIZE THE SPECIFIED USART GPIO PINS 
	//ONLY INITIALIZE RX & TX PINS (FOR ASYNC UART MODE)
	//WILL INITIALIZE CLK PIN ONLY IF USER REQUESTS SYNCHRONOUS MODE
	
	GPIO_InitTypeDef gpio;
	
	#ifdef STM32F103
		if (usart_num == ARM_STM32_USART_PERIPHERAL_USART1)
		{
			gpio.GPIO_Mode = GPIO_Mode_AF_PP;
			gpio.GPIO_Speed = (GPIOSpeed_TypeDef)usart_gpio_speed;
			gpio.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
			GPIO_Init(GPIOA, &gpio);
		}
		else if (usart_num == ARM_STM32_USART_PERIPHERAL_USART2)
		{
			gpio.GPIO_Mode = GPIO_Mode_AF_PP;
			gpio.GPIO_Speed = (GPIOSpeed_TypeDef)usart_gpio_speed;
			gpio.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
			GPIO_Init(GPIOA, &gpio);
		}
	#endif
}

void ARM_STM32_USART_Set_Parameters(uint8_t usart_num, uint16_t usart_mode, uint16_t usart_flow, uint16_t usart_parity, uint16_t usart_stopbits, uint16_t word_len, uint32_t usart_baudrate)
{
	//INITIALIZE THE SPECIFIED USART WITH SPECIFIED PARAMETERS
	
	#ifdef STM32F103
		if (usart_num == ARM_STM32_USART_PERIPHERAL_USART1)
		{
			//USART 1 PERIPHERAL
			
			//ENABLE CLOCK TO USART1
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
			
			//CONFIGURE USART1 PARAMETERS
			USART_InitTypeDef usart;
			usart.USART_Mode = usart_mode;
			usart.USART_HardwareFlowControl = usart_flow;
			usart.USART_Parity = usart_parity;
			usart.USART_StopBits = usart_stopbits;
			usart.USART_WordLength = word_len;
			usart.USART_BaudRate = usart_baudrate;
			
			//INITIALIZE USART1
			USART_Init(USART1, &usart);
		}
		else if (usart_num == ARM_STM32_USART_PERIPHERAL_USART2)
		{
			//USART 2 PERIPHERAL
			
			//ENABLE CLOCK TO USART1
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
			
			//CONFIGURE USART1 PARAMETERS
			USART_InitTypeDef usart;
			usart.USART_Mode = usart_mode;
			usart.USART_HardwareFlowControl = usart_flow;
			usart.USART_Parity = usart_parity;
			usart.USART_StopBits = usart_stopbits;
			usart.USART_WordLength = word_len;
			usart.USART_BaudRate = usart_baudrate;
			
			//INITIALIZE USART1
			USART_Init(USART2, &usart);
		}
	#endif
}

void ARM_STM32_USART_Set_Synchronous_Clock(uint8_t usart_num, uint16_t usart_clk, uint16_t usart_cpha, uint16_t usart_cpol, uint16_t usart_lastbit)
{
	//ENABLE THE CLOCK FOR THE SPECIFIED USART
	//FOR USART SYNCHONOUS MODE . THIS FUNCTION IS NOT CALLED, USART WORKS IN ASYNCHRONOUS MODE(UART)
	
	#ifdef STM32F103
		GPIO_InitTypeDef gpio;
		USART_TypeDef* usart_ptr;
	
		gpio.GPIO_Mode = GPIO_Mode_AF_PP;
		gpio.GPIO_Speed = GPIO_Speed_50MHz;
	
		if (usart_num == ARM_STM32_USART_PERIPHERAL_USART1)
		{
			usart_ptr = USART1;
			gpio.GPIO_Pin = GPIO_Pin_8;
		}
		else if(usart_num == ARM_STM32_USART_PERIPHERAL_USART2)
		{
			usart_ptr = USART2;
			gpio.GPIO_Pin = GPIO_Pin_4;
		}
		
		GPIO_Init(GPIOA, &gpio);
		
		USART_ClockInitTypeDef usart_clock;
		
		usart_clock.USART_Clock = usart_clk;
		usart_clock.USART_CPHA = usart_cpha;
		usart_clock.USART_CPOL = usart_cpol;
		usart_clock.USART_LastBit = usart_lastbit;
		
		USART_ClockInit(usart_ptr, &usart_clock);
	#endif
}

void ARM_STM32_USART_Start(uint8_t usart_num)
{
	//START THE SPECIFIED USART PERIPHERAL
	
	#ifdef STM32F103
		if (usart_num == ARM_STM32_USART_PERIPHERAL_USART1)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
			USART_Cmd(USART1, ENABLE);
		}
		else if (usart_num == ARM_STM32_USART_PERIPHERAL_USART2)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
			USART_Cmd(USART2, ENABLE);
		}
	#endif
}

void ARM_STM32_USART_Stop(uint8_t usart_num)
{
	//DISABLE THE SPECIFIED USART AND REMOVE CLOCK FROM IT
	
	#ifdef STM32F103
		if (usart_num == ARM_STM32_USART_PERIPHERAL_USART1)
		{
			USART_Cmd(USART1, DISABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE);
		}
		else if (usart_num == ARM_STM32_USART_PERIPHERAL_USART2)
		{
			USART_Cmd(USART2, DISABLE);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, DISABLE);
		}
	#endif
}

void ARM_STM32_USART_Send_Char(uint8_t usart_num, uint16_t data)
{
	//SEND SPECIFIED CHARACTER THROUGHT THE SPECIFIED UART
	//LSB FIRST (STM32 USART LIMITATION)
	
	#ifdef STM32F103
		USART_TypeDef* usart_ptr;
	
		if (usart_num == ARM_STM32_USART_PERIPHERAL_USART1)
		{
			usart_ptr = USART1;
		}
		else if (usart_num == ARM_STM32_USART_PERIPHERAL_USART2)
		{
			usart_ptr = USART2;
		}
		USART_SendData(usart_ptr, data);
		
		//WAIT TILL DATA IS SEND
		while(USART_GetFlagStatus(usart_ptr, USART_FLAG_TXE) == RESET){};
	#endif
}

void ARM_STM32_USART_Send_String(uint8_t usart_num, uint16_t* str, uint8_t len)
{
	//SEND THE SUPPLIED CHARACTER STRING OF MENTIONED LENGTH THROUGH SPECIFIED UART
	//LSB FIRST (STM32 USART LIMITATION)
	
	#ifdef STM32F103
	for(uint8_t i=0; i<len; i++)
	{
		ARM_STM32_USART_Send_Char(usart_num, *(str + i));
	}
	#endif
}

uint16_t ARM_STM32_USART_Get_Char(uint8_t usart_num)
{
	//GET AND RETURN CHAR (8/9 BITS) FROM THE SPECIFIED UART
	
	#ifdef STM32F103
		USART_TypeDef* usart_ptr;
	
		if(usart_num == ARM_STM32_USART_PERIPHERAL_USART1)
		{
			usart_ptr = USART1;
		}
		else if(usart_num == ARM_STM32_USART_PERIPHERAL_USART2)
		{
			usart_ptr = USART2;
		}
		
		while(USART_GetFlagStatus(usart_ptr, USART_FLAG_RXNE) == RESET){};
		return USART_ReceiveData(usart_ptr);
	#endif
}

void ARM_STM32_USART_Send_Char_Reversed(uint8_t usart_num, uint16_t data, uint8_t bit_len)
{
	//SEND USART DATA FROM SPECIFIED USART
	//DATA IS REVERSED BEFORE SENDING => MSB FIRST
	//FOR REVERSE OPERATION, NEED TO KNOW THE DATA BIT LEN (8 OR 9) SO THAT CAN PREPARE THE DATA
	//PROPERLY BEFORE SENDING
	
	#ifdef STM32F103
		USART_TypeDef* usart_ptr;
	
		if (usart_num == ARM_STM32_USART_PERIPHERAL_USART1)
		{
			usart_ptr = USART1;
		}
		else if (usart_num == ARM_STM32_USART_PERIPHERAL_USART2)
		{
			usart_ptr = USART2;
		}
		USART_SendData(usart_ptr, (__RBIT(data) >> (32 - bit_len)));
		
		//WAIT TILL DATA IS SEND
		while(USART_GetFlagStatus(usart_ptr, USART_FLAG_TXE) == RESET){};
	#endif
}

void ARM_STM32_USART_Send_String_Reversed(uint8_t usart_num, uint16_t* str, uint8_t len, uint8_t bit_len)
{
	//SEND USART DATA FROM SPECIFIED USART
	//DATA IS REVERSED BEFORE SENDING => MSB FIRST
	//FOR REVERSE OPERATION, NEED TO KNOW THE DATA BIT LEN (8 OR 9) SO THAT CAN PREPARE THE DATA
	//PROPERLY BEFORE SENDING
	
	#ifdef STM32F103
	for(uint8_t i=0; i<len; i++)
	{
		ARM_STM32_USART_Send_Char_Reversed(usart_num, *(str + i), bit_len);
	}
	#endif
}


void ARM_STM32_USART_Deinit(uint8_t usart_num)
{
	//DEINTIALIZE THE USART PERPHERAL REGISTERS
	//TO THEIR DEFAULT VALUES
	
	USART_TypeDef* usart_ptr;
	
	#ifdef STM32F103
	if(usart_num == ARM_STM32_USART_PERIPHERAL_USART1)
	{
		//USART1 PERIPHERAL
		usart_ptr = USART1;
	}
	else if (usart_num == ARM_STM32_USART_PERIPHERAL_USART2)
	{
		//USART2 PERIPHERAL
		usart_ptr = USART2;
	}
	USART_DeInit(usart_ptr);
	#endif
}
