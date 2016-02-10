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



TRetVal CRingBuffer::copyTo( uint8_t * dest, int size, int * actAmount )
{
	if( actAmount )
	{
	  	*actAmount = 0;
	}
	
	return rvOK;
}



TRetVal CRingBuffer::push( uint8_t byte )
{
  	return rvOK;
}
