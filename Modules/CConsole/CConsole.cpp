#include "CConsole.hpp"



#include <CStm32FxxSerialDriver.hpp>
#include <tasksConfig.h>



CConsole * CConsole::_self = 0;



CStm32FxxSerialDriver serial( CStm32FxxSerialDriver::N2 );



void cConsoleWrapper()
{
	//CConsole::getInstance()->exec();
	char data[] = "\r\nHi! This is FreeRTOS console!";
	
	for( ; ; )
	{
		serial.write( data );
		
		delayMs( 1000 );
	}
}