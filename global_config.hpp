/*************************************************************************
 * ��� �����              : config.hpp
 *
 *
 * ��������               : ��������� �������
 *
 *
 *************************************************************************/
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "FreeRTOS.h"
#include "task.h"


#define SYSTEM_CLOCK            48000000UL   

#define delayMs(ms)             vTaskDelay(MSEC(ms))
#define halGetSysCounter()      xTaskGetTickCount()

#ifdef __cplusplus

// �������� ������ USART1
const uint32_t USART1_BAUDRATE          = 115200;
// �������� ������ USART2
const uint32_t USART2_BAUDRATE          = 115200;
// ����-��� ��� ���������������� ������
const int USART_RX_TIMEOUT				= 1000000;
const int USART_TX_TIMEOUT				= 100000;

#endif // __cplusplus

/* ������ ���������� ����� */
// ���� ���������, �� ��� ����� ����� �������� ��� ���������
// ���� �� ���������, �� ����� ��������� �������
#define DEBUG_GLOBAL_NYASHKA


#ifdef DEBUG_GLOBAL_NYASHKA

/* ������� ������, ��������� ���� ������� ���������� ������� */
// ���� ���������, �� � ���� ��������� ���������� �������� ��������� ��������
// �� ���������
#define DEBUG_GENERATE_LIC_FILE

// ����� ��������� ��������� �������� ���������
#define DEBUG_MEAS_STATE_MACHINE

// ����� ���������� ���������� �������������� ������
#define DEBUG_MEAS_CORE_NEW

// ����� ���������� ���������� ������������� �����
#define DEBUG_MEAS_BOARD

// ������ �� ������ ������ ���� (��� ������ ����� �������� surround ex, � ��� ���� �����)
//#define DEBUG_OLD_BOARD

#endif  // DEBUG_GLOBAL_NYASHKA


/** ���� ���������� ����, �� ���������� � �������. ����� � ���� */
#define USE_RTOS		1


#endif
