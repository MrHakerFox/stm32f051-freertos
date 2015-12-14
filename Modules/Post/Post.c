#include "Post.h"



#include <stm32f0xx.h>
#include <gpio_macros.h>



void gpioInit()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;	

	GPIO_MODER( GPIOB, 3, OUT_FUNC_MODE );	
	GPIO_MODER( GPIOB, 4, OUT_FUNC_MODE );	
}