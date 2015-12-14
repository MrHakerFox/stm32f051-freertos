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
uint32_t SystemCoreClock = SYSTEM_CLOCK;



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
