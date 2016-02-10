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
	const char waitign[] = "\r\n>";
	const char nodata[] = "\r\nTimeout";
	const char ok[] = "\r\nok : ";
	static char rxBuff[ 64 ];
	int aread;
	
	TRetVal retVal = serial.open();
    if( retVal != rvOK )
	{
		vTaskSuspend( NULL );
    }
	
	retVal = serial.write( data, sizeof( data ) );
	
	if( retVal != rvOK )
	{
		vTaskSuspend( NULL );
	}	
	
	for( ; ; )
	{	
	  	for ( int i = 0; i < sizeof( rxBuff ); i++ )
		{
		  	rxBuff[ i ] = 0;
		}
	  	serial.write( waitign, sizeof( waitign ) );
	  
		retVal = serial.read( rxBuff, sizeof( rxBuff ), &aread, 5000 );
		
		if ( retVal == rvOK )
		{
		  	serial.write( ok, sizeof( ok ) );
			serial.write( rxBuff, aread );
		}
		else
		{
			serial.write( nodata, sizeof( nodata ) );
		}
	}
}