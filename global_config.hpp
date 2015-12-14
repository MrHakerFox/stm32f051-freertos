/*************************************************************************
 * Имя файла              : config.hpp
 *
 *
 * Описание               : настройки проекта
 *
 *
 *************************************************************************/
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "FreeRTOS.h"
#include "task.h"


#define SYSTEM_CLOCK            48000000UL   
uint32_t SystemCoreClock = SYSTEM_CLOCK;



/* Всякие отладочные няшки */
// Если объявлена, то все няшки можно включать или выключать
// Если не объявлена, то няшки автоматом гасятся
#define DEBUG_GLOBAL_NYASHKA


#ifdef DEBUG_GLOBAL_NYASHKA

/* Начиная отсюда, объявляем наши макросы управления дебагом */
// Если объявлена, то в окне активации появляется кнопочка генерации лицензий
// на юсьфлешку
#define DEBUG_GENERATE_LIC_FILE

// Вывод состояний конечного автомата измерений
#define DEBUG_MEAS_STATE_MACHINE

// Вывод отладочной информации измерительного модуля
#define DEBUG_MEAS_CORE_NEW

// Вывод отладочной информации измерительной платы
#define DEBUG_MEAS_BOARD

// Работа со старой платой Мики (где небыло долби диджитал surround ex, и тач хило висел)
//#define DEBUG_OLD_BOARD

#endif  // DEBUG_GLOBAL_NYASHKA


/** Если используем ОСРВ, то установить в единицу. Иначе в ноль */
#define USE_RTOS		1


#endif
