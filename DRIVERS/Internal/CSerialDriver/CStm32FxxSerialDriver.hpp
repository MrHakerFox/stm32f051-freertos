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
	USART_TypeDef *USARTn;
	TaskHandle_t xTaskToNotify[ TOTAL_USART_NUM ];
	
	
	protected:
	
	
	
	public:
	CStm32FxxSerialDriver( TUartNum num );
	
	TRetVal open();
	
	TRetVal write( const char * data, int size, int timeout = 0 );
	TRetVal read( char * data, int size, int * read, int timeout = 0 );
	
	TRetVal close();
};


#endif
