#ifndef IO_MACROS_H
#define IO_MACROS_H

#include "stm32f0xx.h"

#define GPIOX(port)						port

// GPIOx_MODER function
#define INP_FUNC_MODE   				0
#define OUT_FUNC_MODE   				1
#define ALT_FUNC_MODE   				2
#define ANA_FUNC_MODE   				3

// GPIO port mode
#define REG_GPIO_MODER(port)			( GPIOX(port)->MODER )	
#define GPIO_MODER(port, pin, moder) \
			MODIFICATION_REGISTER(REG_GPIO_MODER(port), pin, 2, 0x03, moder)

// GPIO alternate function
#define ALT_FUNC_0						0
#define ALT_FUNC_1						1
#define ALT_FUNC_2						2
#define ALT_FUNC_3						3
#define ALT_FUNC_4						4
#define ALT_FUNC_5						5
#define ALT_FUNC_6						6
#define ALT_FUNC_7						7
#define REG_GPIO_AFR(port)				( GPIOX(port)->AFR )
#define GPIO_AFR(port, pin, altfunc)	\
			MODIFICATION_REGISTER(REG_GPIO_AFR(port)[pin >> 0x03], \
			(pin & 0x07), 4, 0x0f, altfunc)

// GPIO port bit set
#define REG_GPIO_SET(port)				( GPIOX(port)->BSRR )
#define SET_GPIO_SET(port, pin)			( REG_GPIO_SET(port) |= (1 << pin) )

// GPIO port bit reset
#define REG_GPIO_CLR(port)				( GPIOX(port)->BSRR )
#define SET_GPIO_CLR(port, pin)			( REG_GPIO_CLR(port) |= \
			((1 << pin)) << 16)

// Set Value Port
//#define	LOW									(0)
//#define	HIGH								(1)
#define SET_GPIO(port, pin, value)		( (value) ? \
			( SET_GPIO_SET(port, pin) ) : \
			( SET_GPIO_CLR(port, pin) ) )

// Atomic Set Value Port
#define REG_GPIO_ODR(port)				( GPIOX(port)->ODR )
#define SET_GPIO_ATOMIC(port, pin, value) \
			WRITE_BIT(REG_GPIO_ODR(port), pin, value)
// #define SET_GPIO(GPIO,PIN,VALUE)	((VALUE == 1) ? \
			// (GPIO##_BSRR |= (1 << PIN)) : (GPIO##_BSRR  |= (1 << PIN) << 16))

// Read Value Port
#define REG_GPIO_PIN(port)				( GPIOX(port)->IDR )
#define READ_GPIO_PIN(port, pin)		( REG_GPIO_PIN(port) & (1 << pin) )
#define READ_GPIO_PORT(port)			( REG_GPIO_PIN(port) & 0xffff )

#define PUSHPULL_TYPE					0
#define OPENDRAIN_TYPE					1
#define REG_GPIO_OTYPER(port)			( GPIOX(port)->OTYPER )
#define GPIO_OTYPER(port, pin, value) \
			WRITE_BIT(REG_GPIO_OTYPER(port), pin, value)
	// ( value ? \
	// 		( REG_GPIO_OTYPER(port) |= (1 << pin) ) : \
	// 		( REG_GPIO_OTYPER(port) &= ~(1 << pin) ) )

// GPIO port pull-up/pull-down
#define NO_PULL_PUPD					0
#define PULL_UP_PUPD					1
#define PULL_DOWN_PUPD					2
#define REG_GPIO_PUPDR(port)			( GPIOX(port)->PUPDR )
#define GPIO_PUPDR(port, pin, pupd) \
			MODIFICATION_REGISTER(REG_GPIO_PUPDR(port), pin, 2, 0x03, pupd)

// GPIO port output speed
#define LOW_SPEED						0
#define MEDIUM_SPEED					1
#define HIGH_SPEED						2
#define REG_GPIO_OSPEEDR(port)			( GPIOX(port)->OSPEEDR )
// #define GPIO_OSPEEDR(port, pin, speed) \
// 			do{ REG_GPIO_OSPEEDR(port) &= ~(0x03 << (uint16_t)pin * 2); \
// 			REG_GPIO_OSPEEDR(port) |= (speed << pin * 2); }while(0)

#define GPIO_OSPEEDR(port, pin, speed) \
			MODIFICATION_REGISTER(REG_GPIO_OSPEEDR(port), pin, 2, 0x03, speed)


#define	MODIFICATION_REGISTER(reg, bit, offset, mask, value) \
			do{ reg &= ~(mask << (bit * offset)); \
			reg |= (value << (bit * offset)); }while(0)

#define	WRITE_BIT(reg, bit, value)			( value ? \
			( reg |= (1 << bit) ) : \
			( reg &= ~(1 << bit) ) )

#endif