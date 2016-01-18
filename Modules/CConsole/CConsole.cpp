/**
	\brief Provides the debug terminal. Use any sofware like Putty, Windows
Terminal to communicate with the device
*/



#include "CConsole.hpp"



#include <CStm32FxxSerialDriver.hpp>
#include <tasksConfig.h>



CConsole * CConsole::_self = 0;


#warning change to proxy driver
CStm32FxxSerialDriver serial( CStm32FxxSerialDriver::N1 );



void cConsoleWrapper()
{
	//CConsole::getInstance()->exec();
	const char data[] = "\r\nHi! This is FreeRTOS console!";
	
	TRetVal retVal = serial.open();
    if( retVal != rvOK )
	{
		vTaskSuspend( NULL );
    }
	
	for( ; ; )
	{
		retVal = serial.write( data, sizeof( data ) );
		
		delayMs( 1000 );
	}
}