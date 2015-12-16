#include "CStm32FxxSerialDriver.hpp"



CStm32FxxSerialDriver::CStm32FxxSerialDriver( TUartNum )
{
}



TRetVal CStm32FxxSerialDriver::open()
{
	
	return rvOK;
}



TRetVal CStm32FxxSerialDriver::write( const char * data )
{
	int len = sizeof( *data );
	return rvOK;
}