#ifndef TASKS_CONFIG_H
#define TASKS_CONFIG_H


#include <FreeRTOS.h>
#include <task.h>


void setupTask( void * pvParameters );



#define SETUP_TASK_STACK_SIZE	100



#define SETUP_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )


#endif