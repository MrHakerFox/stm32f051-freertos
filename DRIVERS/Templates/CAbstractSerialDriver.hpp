#ifndef CABSTRACT_SERIAL_DRIVER_HPP
#define CABSTRACT_SERIAL_DRIVER_HPP



#include "CAbstractTemplateDriver.hpp"


namespace SERIAL
{
	enum TIoCtlNum
	{
	};
	
	struct TIoCtlParam
	{
	};
};



class CAbstractSerialDriver :
public CAbstractTemplateDriver< SERIAL::TIoCtlNum, SERIAL::TIoCtlParam >
{
	private:
	
	
	
	protected:
	
	
	
	public:
};



#endif
