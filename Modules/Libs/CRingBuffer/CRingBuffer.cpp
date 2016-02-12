#include "CRingBuffer.hpp"



#include <task.h>



CRingBuffer::CRingBuffer( int s )
{
	buffSize = s;
	pBuff = new uint8_t [ buffSize ];
	
	flush();
}



CRingBuffer::~CRingBuffer()
{
  	delete [] pBuff;
	pBuff= 0;
}




/*!
Function copies all available data from its internal buffer to the destanation

@param *data - to where available data will be copied
@param size - number of bytes that can be stored at destanation
@param *actAmount - actual number of bytes available to copy

\return see RetVals.hpp file
*/
TRetVal CRingBuffer::copyTo( uint8_t * dest, int size, int * actAmount )
{
	if ( !dest )
	{
		return rvSETTING_ERROR;
	}
	
	taskENTER_CRITICAL();
	
	int amount = filledSize > size ? size : filledSize;
	  
	if( actAmount )
	{
		*actAmount = amount;
	}
	
	while( amount-- )
	{
		*dest++ = *( pBuff + pTail );
		if ( ++pTail >= buffSize )
		{
			pTail = 0;
		}
	}
	
	taskEXIT_CRITICAL();
	return rvOK;
}



/*!
Function pushes a byte into internal buffer

@param byte data byte

\return see RetVals.hpp file
*/
TRetVal CRingBuffer::push( uint8_t byte )
{
	taskENTER_CRITICAL();
	
	*( pBuff + pHead ) = byte;
	
	if ( ++pHead >= buffSize )
	{
		pHead = 0;
	}
	
	if ( ++filledSize >= buffSize )
	{
		filledSize = buffSize;
	}
	
	taskEXIT_CRITICAL();
	
  	return rvOK;
}



/*!
Function removes all available elements
*/
void CRingBuffer::flush()
{
	taskENTER_CRITICAL();
	pTail = 0;
	pHead = 0;
	filledSize = 0;
	taskEXIT_CRITICAL();
}
