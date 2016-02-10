/**
	\brief Implementation of serial ports of STM32Fxx devices
*/



#include "CStm32FxxSerialDriver.hpp"



#include <stm32f0xx.h>
#include <gpio_macros.h>
#include <FreeRTOS.h>


TaskHandle_t CStm32FxxSerialDriver::xTaskToNotifyTx[ TOTAL_USART_NUM ];
TaskHandle_t CStm32FxxSerialDriver::xTaskToNotifyRx[ TOTAL_USART_NUM ];
const char * CStm32FxxSerialDriver::txDataPtr[ TOTAL_USART_NUM ];
int CStm32FxxSerialDriver::txSize[ TOTAL_USART_NUM ];
USART_TypeDef *CStm32FxxSerialDriver::USARTn[ TOTAL_USART_NUM ];
CRingBuffer * CStm32FxxSerialDriver::rxRingBuffer[ TOTAL_USART_NUM ];



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
		
		USARTn[ hdwNum ] = USART1;
		
		rxRingBuffer[ hdwNum ] = new CRingBuffer( USART1_INSTANT_GET_MAX_BYTE );
		
		USARTn[ hdwNum ]->CR1 |= USART_CR1_RXNEIE;
		
		NVIC_EnableIRQ( USART1_IRQn );
		break;
		
		case N2:
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		
		GPIO_MODER(USART2_TX_PORT, USART2_TX_PIN, ALT_FUNC_MODE);
		GPIO_AFR(USART2_TX_PORT, USART2_TX_PIN, ALT_FUNC_1);
		GPIO_MODER(USART2_RX_PORT, USART2_RX_PIN, ALT_FUNC_MODE);
		GPIO_AFR(USART2_RX_PORT, USART2_RX_PIN, ALT_FUNC_1);
		
		USART2->BRR = ( uint32_t )( (float)SYSTEM_CLOCK / ( float )USART2_DEFAULT_BAUDRATE );
		
		rxRingBuffer[ hdwNum ] = new CRingBuffer( USART2_INSTANT_GET_MAX_BYTE );
		
		NVIC_EnableIRQ( USART2_IRQn );
		
		USARTn[ hdwNum ] = USART2;

		break;
	}

	
	USARTn[ hdwNum ]->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
	
	return rvOK;
}



/*!
Use the function to write some buffer

@param *data - pointer to the data to be transmitted
@param size - size of data buffer
@param timeout - timeout (ms) for ALL the data to be sent

\return see RetVals.hpp file
*/
TRetVal CStm32FxxSerialDriver::write( const char * data, int size, int timeout )
{
  	if ( !size || !data )
	{
	  	return rvOK;
	}
  
	CStm32FxxSerialDriver::xTaskToNotifyTx[ hdwNum ] = xTaskGetCurrentTaskHandle();
	
	txDataPtr[ hdwNum ] = data;
	txSize[ hdwNum ] = size;
	
	USARTn[ hdwNum ]->CR1 |= USART_CR1_TXEIE;
	
	uint32_t ulNotificationValue = ulTaskNotifyTake( pdTRUE, pdMS_TO_TICKS( timeout ) );
	
	USARTn[ hdwNum ]->CR1 &= ~USART_CR1_TXEIE;
	
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
  	CStm32FxxSerialDriver::xTaskToNotifyRx[ hdwNum ] = xTaskGetCurrentTaskHandle();
	
	uint32_t ulNotificationValue = ulTaskNotifyTake( pdTRUE, pdMS_TO_TICKS( timeout ) );
	
	rxRingBuffer[ hdwNum ]->copyTo( ( uint8_t * )&data, size, read );
	
	USARTn[ hdwNum ]->CR1 |= USART_CR1_RXNEIE;
	
	return ulNotificationValue == 1 ? rvOK : rvTIME_OUT;
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
	
	/** TXE interrupt */
	while ( CStm32FxxSerialDriver::USARTn[ num ]->ISR & USART_ISR_TXE && CStm32FxxSerialDriver::txSize[ num ]  )
	{
		CStm32FxxSerialDriver::USARTn[ num ]->TDR = *CStm32FxxSerialDriver::txDataPtr[ num ]++;
		if ( --CStm32FxxSerialDriver::txSize[ num ] == 0 )
		{
			CStm32FxxSerialDriver::USARTn[ num ]->CR1 &= ~USART_CR1_TXEIE;
			vTaskNotifyGiveFromISR( CStm32FxxSerialDriver::xTaskToNotifyTx[ num ], &xHigherPriorityTaskWoken );
			break;
		}
	}
	
	/** RXNE interrupt */
	while ( CStm32FxxSerialDriver::USARTn[ num ]->ISR & USART_ISR_RXNE )
	{
		uint8_t byte = CStm32FxxSerialDriver::USARTn[ num ]->RDR;
		if ( byte == '\n' )
		{
		  	USARTn[ num ]->CR1 &= ~USART_CR1_RXNEIE;
			vTaskNotifyGiveFromISR( CStm32FxxSerialDriver::xTaskToNotifyRx[ num ], &xHigherPriorityTaskWoken );
			break;
		}
		CStm32FxxSerialDriver::rxRingBuffer[ num ]->push( byte );
	}
	
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
