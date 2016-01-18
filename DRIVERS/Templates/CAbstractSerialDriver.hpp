/**
	\brief Abstract serial driver. It may by used as a base to create driver
*/


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
