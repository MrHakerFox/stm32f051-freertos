/**
	\brief Implementation of serial ports of STM32Fxx devices
*/



#include "CStm32FxxSerialDriver.hpp"



#include <stm32f0xx.h>
#include <gpio_macros.h>
#include <FreeRTOS.h>


TaskHandle_t CStm32FxxSerialDriver::xTaskToNotify[ TOTAL_USART_NUM ];



extern "C" void USART1_IRQHandler()
{
	CStm32FxxSerialDriver::isrService( CStm32FxxSerialDriver::N1 );
	NVIC_ClearPendingIRQ( USART1_IRQn );
}



extern "C" void USART2_IRQHandler()
{
	CStm32FxxSerialDriver::isrService( CStm32FxxSerialDriver::N2 );
	NVIC_ClearPendingIRQ( USART2_IRQn );
}



CStm32FxxSerialDriver::CStm32FxxSerialDriver( TUartNum num )
{
	hdwNum = num;
}



/*!
Before using serial port you must call open() function

\return see RetVals.hpp file
*/
TRetVal CStm32FxxSerialDriver::open()
{
	int sendBuffSize, getBuffSize;
	
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	switch( hdwNum )
	{
		case N1:
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		
		GPIO_MODER(USART1_TX_PORT, USART1_TX_PIN, ALT_FUNC_MODE);
		GPIO_AFR(USART1_TX_PORT, USART1_TX_PIN, ALT_FUNC_1);
		GPIO_MODER(USART1_RX_PORT, USART1_RX_PIN, ALT_FUNC_MODE);
		GPIO_AFR(USART1_RX_PORT, USART1_RX_PIN, ALT_FUNC_1);	
		
		USART1->BRR = ( uint32_t )( (float)SYSTEM_CLOCK / ( float )USART1_DEFAULT_BAUDRATE );
		
		USARTn = USART1;
		
		sendBuffSize = USART1_INSTANT_SEND_MAX_BYTE;
		getBuffSize = USART1_INSTANT_GET_MAX_BYTE;
		break;
		
		case N2:
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		
		GPIO_MODER(USART2_TX_PORT, USART2_TX_PIN, ALT_FUNC_MODE);
		GPIO_AFR(USART2_TX_PORT, USART2_TX_PIN, ALT_FUNC_1);
		GPIO_MODER(USART2_RX_PORT, USART2_RX_PIN, ALT_FUNC_MODE);
		GPIO_AFR(USART2_RX_PORT, USART2_RX_PIN, ALT_FUNC_1);
		
		USART2->BRR = ( uint32_t )( (float)SYSTEM_CLOCK / ( float )USART2_DEFAULT_BAUDRATE );
		
		USARTn = USART2;
		
		sendBuffSize = USART2_INSTANT_SEND_MAX_BYTE;
		getBuffSize = USART2_INSTANT_GET_MAX_BYTE;
		break;
	}
	
	//buffPtr = ( uint8_t * )pvPortMalloc( sendBuffSize );
	
	
	USARTn->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
	
	return rvOK;
}



/*!
Use the function to write some buffer

@param *data - pointer to the data to be transmitted
@param size - size of data buffer
@param timeout - timeout (ms) for ALL the data

\return see RetVals.hpp file
*/
TRetVal CStm32FxxSerialDriver::write( const char * data, int size, int timeout )
{
	CStm32FxxSerialDriver::xTaskToNotify[ hdwNum ] = xTaskGetCurrentTaskHandle();
	
	uint32_t ulNotificationValue = ulTaskNotifyTake( pdTRUE, pdMS_TO_TICKS( timeout ) );
	
	return ulNotificationValue == 1 ? rvOK : rvTIME_OUT;
}



/*!
Use the function to read some data

@param *data - pointer to the data to be read
@param size - size of buffer where the data will be placed
@param *read - pointer to the variable where actual number of read bytes will be placed
@param timeout - timeout in milliseconds

\return see RetVals.hpp file
*/
TRetVal CStm32FxxSerialDriver::read( char * data, int size, int * read, int timeout )
{
}



/*!
Use the function to close the driver

\return see RetVals.hpp file
*/
TRetVal CStm32FxxSerialDriver::close()
{
	return rvOK;
}



/*!
This is an Interrupt Service Routine

@param num - number of physical usart
*/
void CStm32FxxSerialDriver::isrService( TUartNum num)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	
	vTaskNotifyGiveFromISR( CStm32FxxSerialDriver::xTaskToNotify[ num ], &xHigherPriorityTaskWoken );
	
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
