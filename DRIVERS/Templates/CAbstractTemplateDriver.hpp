#ifndef CABSTRACT_DRIVER_TEMPLATE_HHP
#define CABSTRACT_DRIVER_TEMPLATE_HHP



#include <RetVals.hpp>



template< class TIoCtlNum, class TIoCtlParam >
class CAbstractTemplateDriver
{
	private:
	
	
	
	protected:
	
	
	
	public:
	virtual TRetVal open();
	
	virtual TRetVal write( const char * data );
	virtual TRetVal read( char * data, int read, int timeout = 0 );
	
	virtual TRetVal close();
	
	virtual TRetVal ioctl( TIoCtlNum num, TIoCtlParam * param );
};


#endif
