#include "tasksConfig.h"



#include <gpio_macros.h>



#define LIVE_LED_PORT	GPIOB
#define LIVE_LED_PIN	3



void liveLedTask( void * pvParameters )
{	
	for( ; ; )
	{
		delayMs( 10 );
		SET_GPIO_SET( LIVE_LED_PORT, LIVE_LED_PIN );
		delayMs( 10 );
		SET_GPIO_CLR( LIVE_LED_PORT, LIVE_LED_PIN );
	}
}