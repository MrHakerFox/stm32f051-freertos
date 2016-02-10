#ifndef CSTM32FXX_SERIAL_DRIVER_HPP
#define CSTM32FXX_SERIAL_DRIVER_HPP



#include <CAbstractSerialDriver.hpp>
#include "CStm32FxxSerialDriverConfig.hpp"



#include <stm32f0xx.h>
#include <global_config.hpp>
#include <CRingBuffer.hpp>




class CStm32FxxSerialDriver : 	public CAbstractSerialDriver
{
	public:
	/** Physical number of STM32FXX */
	enum TUartNum { N1 = 0, N2 = 1 };	
	
	
	
	private:
	TUartNum hdwNum;
	static USART_TypeDef *USARTn[ TOTAL_USART_NUM ];
	static TaskHandle_t xTaskToNotifyTx[ TOTAL_USART_NUM ];
	static TaskHandle_t xTaskToNotifyRx[ TOTAL_USART_NUM ];
	static const char * txDataPtr[ TOTAL_USART_NUM ];
	static int txSize[ TOTAL_USART_NUM ];
	static CRingBuffer * rxRingBuffer[ TOTAL_USART_NUM ];
	
	
	protected:
	
	
	
	public:
	CStm32FxxSerialDriver( TUartNum num );
	
	TRetVal open();
	
	TRetVal write( const char * data, int size, int timeout = USART_TX_TIMEOUT );
	TRetVal read( char * data, int size, int * read, int timeout = USART_RX_TIMEOUT );
	
	TRetVal close();
	
	static void isrService( TUartNum num);
};


#endif
