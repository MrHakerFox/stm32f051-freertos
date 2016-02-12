#ifndef TASKS_CONFIG_H
#define TASKS_CONFIG_H


#include <FreeRTOS.h>
#include <task.h>


void setupTask( void * pvParameters );
void consoleTask( void * pvParameters );
void liveLedTask( void * pvParameters );
void linkTask( void * pvParameters );



#define SETUP_TASK_STACK_SIZE	100
#define CONSOLE_TASK_STACK_SIZE	256
#define LIVELED_TASK_STACK_SIZE	100
#define LINK_TASK_STACK_SIZE	100



#define SETUP_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )
#define CONSOLE_TASK_PRIORITY	( tskIDLE_PRIORITY + 1 )
#define LIVELED_TASK_PRIORITY	( tskIDLE_PRIORITY + 1 )
#define LINK_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )


#endif