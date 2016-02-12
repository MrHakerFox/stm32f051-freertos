/**
\brief Setup task
This task creates all needed task then is deletet by itselfs
*/


#include "tasksConfig.h"



#include <gpio_macros.h>



TaskHandle_t consoleTaskHandle;
TaskHandle_t liveLedTaskHandle;
TaskHandle_t linkTaskHandle;





void setupTask( void * pvParameters )
{
	BaseType_t consoleTaskResult = xTaskCreate(
										consoleTask,
										"console",
										CONSOLE_TASK_STACK_SIZE,
										( void * )NULL,
										CONSOLE_TASK_PRIORITY,
										&consoleTaskHandle );	
	
	BaseType_t liveLedTaskResult = xTaskCreate(
										liveLedTask,
										"liveLed",
										LIVELED_TASK_STACK_SIZE,
										( void * )NULL,
										LIVELED_TASK_PRIORITY,
										&liveLedTaskHandle );	
	
	BaseType_t linkTaskResult = xTaskCreate(
										linkTask,
										"link",
										LINK_TASK_STACK_SIZE,
										( void * )NULL,
										LINK_TASK_PRIORITY,
										&linkTaskHandle );		
	
	vTaskDelete( NULL );
}
