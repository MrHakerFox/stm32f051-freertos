#ifndef CRING_BUFFER_HPP
#define CRING_BUFFER_HPP



#include <inttypes.h>



#include <RetVals.hpp>
#include <FreeRTOS.h>
#include <semphr.h>



class CRingBuffer
{
	private:
	SemaphoreHandle_t dataAvailSemaphore;

	
	protected:
	int buffSize;
	uint8_t * buffPtr;
	
	volatile int head;
	volatile int tail;	
	

	public:
	CRingBuffer( int size );
	CRingBuffer();
	~CRingBuffer();
	
	void setSize( int s );
	
	void push( char c );
	char pop();
	
	TRetVal copyTo( uint8_t * dst, int size, int * read, int timeout );
	
	bool isFull() const;
	bool isEmpty() const;
	
	int getSize() const { return buffSize; }
	
	void flush();
};



#endif
