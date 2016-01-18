/**
	\brief This template is a base for creating any drivers
*/



#ifndef CABSTRACT_DRIVER_TEMPLATE_HHP
#define CABSTRACT_DRIVER_TEMPLATE_HHP



#include <RetVals.hpp>



template< class TIoCtlNum, class TIoCtlParam >
class CAbstractTemplateDriver
{
	private:
	
	
	
	protected:
	
	
	
	public:
	virtual TRetVal open() { return rvFAILED; }
	
	virtual TRetVal write( const char * data, int size, int timeout = 0 )  { return rvFAILED; }
	virtual TRetVal read( char * data, int size, int read, int timeout = 0 )  { return rvFAILED; }
	
	virtual TRetVal close()  { return rvFAILED; }
	
	virtual TRetVal ioctl( TIoCtlNum num, TIoCtlParam * param )  { return rvFAILED; }
};


#endif
