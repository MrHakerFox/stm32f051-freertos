#ifndef CRING_BUFFER_HPP
#define CRING_BUFFER_HPP



#include <inttypes.h>



class CRingBuffer
{
	private:


	
	protected:
	int buffSize;
	uint8_t * buffPtr;
	
	volatile int head;
	volatile int tail;	
	

	public:
	CRingBuffer( int size );
	CRingBuffer() { buffPtr = 0; buffSize = 0; }
	~CRingBuffer();
	
	void push( char c );
	char pop();
	
	int copyTo( uint8_t * src );
	
	bool isFull() const;
	bool isEmpty() const;
	
	int getSize() const { return buffSize; }
	
	void flush();
};



#endif
