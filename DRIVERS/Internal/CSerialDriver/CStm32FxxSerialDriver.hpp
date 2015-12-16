#ifndef CSTM32FXX_SERIAL_DRIVER_HPP
#define CSTM32FXX_SERIAL_DRIVER_HPP



#include <CAbstractSerialDriver.hpp>







class CSerialDriver : public CAbstractSerialDriver
{
	private:
	
	
	
	protected:
	
	
	
	public:
	
	/** Physical number of STM32FXX */
	enum TUartNum { N1, N2 };
	
	TRetVal open( TUartNum num );
};


#endif
