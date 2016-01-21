/**
	\brief Debug console task
*/



#include "tasksConfig.h"



#include <gpio_macros.h>
#include <CConsole.hpp>



void consoleTask( void * pvParameters )
{  
	cConsoleWrapper();
}
