#include "CRingBuffer.hpp"



#include <task.h>



CRingBuffer::CRingBuffer( int size )
{
	pBuff = new uint8_t [ size ];
	pTail = 0;
	pHead = 0;
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
	if( actAmount )
	{
	  	*actAmount = 0;
	}
	
	return rvOK;
}



/*!
Function pushes a byte into internal buffer

@param byte data byte

\return see RetVals.hpp file
*/
TRetVal CRingBuffer::push( uint8_t byte )
{
  	return rvOK;
}
