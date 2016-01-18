#include "tasksConfig.h"



#include <gpio_macros.h>



#define LIVE_LED_PORT	GPIOA
#define LIVE_LED_PIN	11



void liveLedTask( void * pvParameters )
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;	

	GPIO_MODER( LIVE_LED_PORT, LIVE_LED_PIN, OUT_FUNC_MODE );	
    
	for( ; ; )
	{
		delayMs( 500 );
		SET_GPIO_SET( LIVE_LED_PORT, LIVE_LED_PIN );
		delayMs( 500 );
		SET_GPIO_CLR( LIVE_LED_PORT, LIVE_LED_PIN );
	}
}