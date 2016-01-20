#include "tasksConfig.h"



#include <gpio_macros.h>



#define LIVE_LED_PORT	GPIOA
#define LIVE_LED_PIN	11



enum TModuleWorkingMode
{
  	tmwmNormal,
	tmwmNoLink,
	tmwmHSError,
};


static enum TModuleWorkingMode moduleWorkingMode = tmwmHSError;



void liveLedTask( void * pvParameters )
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;	

	GPIO_MODER( LIVE_LED_PORT, LIVE_LED_PIN, OUT_FUNC_MODE );	
    
	for( ; ; )
	{
	  	if ( moduleWorkingMode == tmwmNormal )
		{
			delayMs( 500 );
			SET_GPIO_SET( LIVE_LED_PORT, LIVE_LED_PIN );
			delayMs( 500 );
			SET_GPIO_CLR( LIVE_LED_PORT, LIVE_LED_PIN );
		}
		
	  	if ( moduleWorkingMode == tmwmNoLink )
		{
			delayMs( 100 );
			SET_GPIO_SET( LIVE_LED_PORT, LIVE_LED_PIN );
			delayMs( 100 );
			SET_GPIO_CLR( LIVE_LED_PORT, LIVE_LED_PIN );
		}
		
		if ( moduleWorkingMode == tmwmHSError )
		{
		  	SET_GPIO_CLR( LIVE_LED_PORT, LIVE_LED_PIN );
			delayMs( 1000 );
			SET_GPIO_SET( LIVE_LED_PORT, LIVE_LED_PIN );
			delayMs( 300 );
			
			SET_GPIO_CLR( LIVE_LED_PORT, LIVE_LED_PIN );
			delayMs( 300 );
			SET_GPIO_SET( LIVE_LED_PORT, LIVE_LED_PIN );
			delayMs( 1000 );
		}		
	}
}