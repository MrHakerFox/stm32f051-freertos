#include "Post.h"



#include <stm32f0xx.h>
#include <gpio_macros.h>



/*!
Only set up the system clock
*/
void systemClockInit()
{
	if( cSysClockWrapper( HSE ) )
	{
    	for( ;; );
  	}
}
