#ifndef CSTM32FXX_SERIAL_DRIVER_CONFIG_HPP
#define CSTM32FXX_SERIAL_DRIVER_CONFIG_HPP


#define USART1_TX_PORT                  GPIOA
#define USART1_TX_PIN                   9
#define USART1_RX_PORT                  GPIOA
#define USART1_RX_PIN                   10

#define USART2_TX_PORT                  GPIOA
#define USART2_TX_PIN                   14
#define USART2_RX_PORT                  GPIOA
#define USART2_RX_PIN                   15



const int TOTAL_USART_NUM				= 2;



const int USART1_DEFAULT_BAUDRATE		= 115200;
const int USART2_DEFAULT_BAUDRATE		= 115200;


const int USART1_INSTANT_GET_MAX_BYTE	= 128;
const int USART2_INSTANT_GET_MAX_BYTE	= 128;

const int USART_TX_TIMEOUT				= 10;
const int USART_RX_TIMEOUT				= 10;


#endif
