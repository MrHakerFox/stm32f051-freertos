#include "CSysClock.hpp"

#include <stm32f0xx.h>
#include <core_cm0.h>
#include <global_config.hpp>


//#define MCO_ENABLE

int CSysClock::init( TSysClockType source_clock)
{
	switch(source_clock)
	{
		
		case HSE:
		// Включаем кварцевый генератор
		if( !( RCC->CR & RCC_CR_HSERDY ) )
		{
			RCC->CR |= RCC_CR_HSEON;
			while( !( RCC->CR & RCC_CR_HSERDY ) );
		}
		RCC->CFGR |= RCC_CFGR_SW_HSE; // Переход на HSE на случай незапуска PLL
		
		RCC->CR &= ~RCC_CR_PLLON;     // Останавливаем PLL
		while ( RCC->CR & RCC_CR_PLLRDY );
		// Настраиваем PLL на выходную частоту 48 МГц
		
		RCC->CFGR &= ~(RCC_CFGR_PLLMULL | RCC_CFGR_PLLSRC | RCC_CFGR_SW);
		RCC->CFGR |= RCC_CFGR_PLLMULL4 | RCC_CFGR_SW_PLL | RCC_CFGR_PLLSRC_PREDIV1;
		RCC->CR |= RCC_CR_PLLON; 
		while (!( RCC->CR & RCC_CR_PLLRDY ));
		// Ожидает переключения на PLL
		while ( (RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
		
		// Отключаем внутренний RC-генератор 8 МГц
		if( RCC->CR & RCC_CR_HSIRDY )
		{
			RCC->CR &= ~RCC_CR_HSION;
			while( RCC->CR & RCC_CR_HSIRDY );
		}
		
		break;
		
		case HSI:
		RCC->CR &= ~RCC_CR_HSEON;
		while ( RCC->CR & RCC_CR_HSERDY );
		
		if( !(RCC->CR & RCC_CR_HSIRDY) ) {
			RCC->CR |= RCC_CR_HSION;
			while (!( RCC->CR & RCC_CR_HSIRDY ));
		}
		RCC->CFGR |= RCC_CFGR_SW_HSI; // Переход на HSI на случай незапуска PLL
		
		RCC->CR &= ~RCC_CR_PLLON;     // Останавливаем PLL
		while ( RCC->CR & RCC_CR_PLLRDY );
		// Настраиваем PLL на выходную частоту 48 МГц
		RCC->CFGR &= ~(RCC_CFGR_PLLMULL | RCC_CFGR_PLLSRC | RCC_CFGR_SW);
		RCC->CFGR |= RCC_CFGR_PLLMULL12 | RCC_CFGR_SW_PLL | RCC_CFGR_PLLSRC_HSI_Div2;
		RCC->CR |= RCC_CR_PLLON; 
		while (!( RCC->CR & RCC_CR_PLLRDY ));
		// Ожидает переключения на PLL
		while ( (RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
		break;
		
		default:
		for( ;; );
	}
	
	// Отладочный вывод клока системной шины (SysClk) на порт PA8
#ifdef MCO_ENABLE
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;  // Подадим тактирование на PORTА
	GPIO_MODER(GPIOA, 8, ALT_FUNC_MODE);
	GPIO_OSPEEDR(GPIOA, 8, HIGH_SPEED);
	GPIO_AFR(GPIOA, 8, ALT_FUNC_0);
	RCC->CFGR &= ~(RCC_CFGR_MCO | 0x80000000);
	RCC->CFGR |= RCC_CFGR_MCO_SYSCLK; // System clock selected as MCO source
#endif
	
	if (SysTick_Config((uint32_t)SYSTEM_CLOCK / 1000))
		return 1;
	
	return 0;
}


int cSysClockWrapper( TSysClockType source )
{
	return CSysClock::init( source );
}

