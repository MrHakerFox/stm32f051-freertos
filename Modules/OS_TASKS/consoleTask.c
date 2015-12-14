#include "tasksConfig.h"



#include <gpio_macros.h>



void consoleTask( void * pvParameters )
{
	for( ; ; )
	{
		vTaskDelay( MSEC( 20 ) );
		SET_GPIO_SET( GPIOB, 4 );
		vTaskDelay( MSEC( 20 ) );
		SET_GPIO_CLR( GPIOB, 4 );
	}
}
