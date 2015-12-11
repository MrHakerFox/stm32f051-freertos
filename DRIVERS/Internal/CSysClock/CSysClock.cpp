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
		// �������� ��������� ���������
		if( !( RCC->CR & RCC_CR_HSERDY ) )
		{
			RCC->CR |= RCC_CR_HSEON;
			while( !( RCC->CR & RCC_CR_HSERDY ) );
		}
		RCC->CFGR |= RCC_CFGR_SW_HSE; // ������� �� HSE �� ������ ��������� PLL
		
		RCC->CR &= ~RCC_CR_PLLON;     // ������������� PLL
		while ( RCC->CR & RCC_CR_PLLRDY );
		// ����������� PLL �� �������� ������� 48 ���
		
		RCC->CFGR &= ~(RCC_CFGR_PLLMULL | RCC_CFGR_PLLSRC | RCC_CFGR_SW);
		RCC->CFGR |= RCC_CFGR_PLLMULL4 | RCC_CFGR_SW_PLL | RCC_CFGR_PLLSRC_PREDIV1;
		RCC->CR |= RCC_CR_PLLON; 
		while (!( RCC->CR & RCC_CR_PLLRDY ));
		// ������� ������������ �� PLL
		while ( (RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
		
		// ��������� ���������� RC-��������� 8 ���
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
		RCC->CFGR |= RCC_CFGR_SW_HSI; // ������� �� HSI �� ������ ��������� PLL
		
		RCC->CR &= ~RCC_CR_PLLON;     // ������������� PLL
		while ( RCC->CR & RCC_CR_PLLRDY );
		// ����������� PLL �� �������� ������� 48 ���
		RCC->CFGR &= ~(RCC_CFGR_PLLMULL | RCC_CFGR_PLLSRC | RCC_CFGR_SW);
		RCC->CFGR |= RCC_CFGR_PLLMULL12 | RCC_CFGR_SW_PLL | RCC_CFGR_PLLSRC_HSI_Div2;
		RCC->CR |= RCC_CR_PLLON; 
		while (!( RCC->CR & RCC_CR_PLLRDY ));
		// ������� ������������ �� PLL
		while ( (RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
		break;
		
		default:
		for( ;; );
	}
	
	// ���������� ����� ����� ��������� ���� (SysClk) �� ���� PA8
#ifdef MCO_ENABLE
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;  // ������� ������������ �� PORT�
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

