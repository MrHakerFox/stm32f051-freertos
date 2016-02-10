#ifndef CRING_BUFFER_HPP
#define CRING_BUFFER_HPP



#include <inttypes.h>



#include <RetVals.hpp>
#include <FreeRTOS.h>
#include <semphr.h>



class CRingBuffer
{
	private:
	uint8_t * pBuff;
	int pTail;
	int pHead;
	
	protected:
	
	
	
	public:
	CRingBuffer( int size );
	~CRingBuffer();
	
	TRetVal copyTo( uint8_t * dest, int size, int * actAmount );
	TRetVal push( uint8_t byte );
};



#endif
