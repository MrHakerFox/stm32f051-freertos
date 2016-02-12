#ifndef CRING_BUFFER_HPP
#define CRING_BUFFER_HPP



#include <inttypes.h>



#include <RetVals.hpp>
#include <FreeRTOS.h>
#include <semphr.h>



class CRingBuffer
{
	private:
	int buffSize;
	int filledSize;	/** How many bytes are stored int he buff */
	uint8_t * pBuff;
	int pTail;
	int pHead;	/** Points to current free element */
	
	protected:
	
	
	
	public:
	CRingBuffer( int s );
	~CRingBuffer();
	
	TRetVal copyTo( uint8_t * dest, int size, int * actAmount );
	TRetVal push( uint8_t byte );
	
	void flush();
};



#endif
