#include "CRingBuffer.hpp"





CRingBuffer::CRingBuffer( int size )
{
	buffSize = 0;
	buffPtr = 0;
	setSize( size );
	flush();
	
	dataAvailSemaphore = xSemaphoreCreateBinary();
}



CRingBuffer::CRingBuffer()
{
	buffPtr = 0;
	buffSize = 0;
	
	dataAvailSemaphore = xSemaphoreCreateBinary();
	
	flush();	
}



CRingBuffer::~CRingBuffer()
{

}



void CRingBuffer::push( char c )
{	
	*( buffPtr + head ) = c;
	
	head++;
	
	if( head >= getSize() )
	{
		head = 0;
	}
}



char CRingBuffer::pop()
{
	char result = *( buffPtr + tail );
	
	tail++;
	if( tail >= getSize() )
	{
		tail = 0;
	}
	
	return result;
}



//bool CRingBuffer::isFull() const
//{
//	return buffCounter == getSize();
//}



//bool CRingBuffer::isEmpty() const
//{
//	return !buffCounter;;
//}


void CRingBuffer::flush()
{
	head = 0;
	tail = 0;	
}



void CRingBuffer::setSize( int s )
{
}



TRetVal CRingBuffer::copyTo( uint8_t * dst, int size, int * read, int timeout )
{
}
