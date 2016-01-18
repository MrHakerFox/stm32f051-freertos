#ifndef CSTM32FXX_SERIAL_DRIVER_HPP
#define CSTM32FXX_SERIAL_DRIVER_HPP



#include <CAbstractSerialDriver.hpp>



#include <stm32f0xx.h>
#include <global_config.hpp>
#include <CRingBuffer.hpp>



#define USART1_TX_PORT                  GPIOA
#define USART1_TX_PIN                   9
#define USART1_RX_PORT                  GPIOA
#define USART1_RX_PIN                   10

#define USART2_TX_PORT                  GPIOA
#define USART2_TX_PIN                   14
#define USART2_RX_PORT                  GPIOA
#define USART2_RX_PIN                   15




#warning to config file
const int USART1_DEFAULT_BAUDRATE		= 115200;
const int USART2_DEFAULT_BAUDRATE		= 115200;

const int USART1_INSTANT_SEND_MAX_BYTE	= 128;
const int USART1_INSTANT_GET_MAX_BYTE	= 128;

const int USART2_INSTANT_SEND_MAX_BYTE	= 128;
const int USART2_INSTANT_GET_MAX_BYTE	= 128;

const int USART1_TX_TIMEOUT				= 10;
const int USART1_RX_TIMEOUT				= 10;

const int USART2_TX_TIMEOUT				= 10;
const int USART2_RX_TIMEOUT				= 10;






class CStm32FxxSerialDriver : 	public CAbstractSerialDriver
{
	public:
	/** Physical number of STM32FXX */
	enum TUartNum { N1, N2 };	
	
	private:
	TUartNum hdwNum;
	USART_TypeDef *USARTn;
	
	
	protected:
	
	
	
	public:
	CStm32FxxSerialDriver( TUartNum num );
	
	TRetVal open();
	
	TRetVal write( const char * data, int size, int timeout = 0 );
};


#endif
