#include "CRingBuffer.hpp"





CRingBuffer::CRingBuffer( int size )
{
	buffSize = size;
#warning change to memmanager
	//buffPtr = new uint8_t[ size ];
	
	flush();
}



CRingBuffer::~CRingBuffer()
{
#warning change to memmanager
	//delete [] buffPtr;
}



void CRingBuffer::push( char c )
{	
	*( buffPtr + head ) = c;
	
	head++;
	
	if( head == getSize() )
	{
		head = 0;
	}
}



char CRingBuffer::pop()
{
	char result = *( buffPtr + tail );
	
	tail++;
	if( tail == getSize() )
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



int CRingBuffer::copyTo( uint8_t * src )
{
}
