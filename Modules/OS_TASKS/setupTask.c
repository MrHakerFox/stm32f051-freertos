/**
\brief Setup task
This task creates all needed task then is deletet by itselfs
*/


#include "tasksConfig.h"



#include <gpio_macros.h>



void setupTask( void * pvParameters )
{
	BaseType_t consoleTaskResult = xTaskCreate(
										consoleTask,
										"console",
										CONSOLE_TASK_STACK_SIZE,
										( void * )NULL,
										CONSOLE_TASK_PRIORITY,
										NULL );	
	
	BaseType_t liveLedTaskResult = xTaskCreate(
										liveLedTask,
										"liveLed",
										LIVELED_TASK_STACK_SIZE,
										( void * )NULL,
										LIVELED_TASK_PRIORITY,
										NULL );	
	
	vTaskDelete( NULL );
}
