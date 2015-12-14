#include "tasksConfig.h"



#include <gpio_macros.h>



void setupTask( void * pvParameters )
{
	for( ; ; )
	{
		vTaskDelay( MSEC( 10 ) );
		SET_GPIO_SET( GPIOB, 3 );
		vTaskDelay( MSEC( 10 ) );
		SET_GPIO_CLR( GPIOB, 3 );
	}
}
