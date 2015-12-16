#ifndef CSTM32FXX_SERIAL_DRIVER_HPP
#define CSTM32FXX_SERIAL_DRIVER_HPP



#include <CAbstractSerialDriver.hpp>







class CStm32FxxSerialDriver : public CAbstractSerialDriver
{
	private:
	
	
	
	protected:
	
	
	
	public:
	
	/** Physical number of STM32FXX */
	enum TUartNum { N1, N2 };
	
	CStm32FxxSerialDriver( TUartNum );
	
	TRetVal open();
	
	TRetVal write( const char * data );
};


#endif
