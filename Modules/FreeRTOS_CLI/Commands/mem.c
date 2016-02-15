#include "commands.h"



#include <string.h>
#include <stdio.h>



#include <heap_z.h>
#include <kprint.h>



typedef enum { DONE, HEAPS, END } TMemCmdState;



BaseType_t memCommand( char *pcWriteBuffer,
                       size_t xWriteBufferLen,
                       const char *pcCommandString )
{
	static TMemCmdState commandDone = DONE;
	static heap_mcb * mcb;	
	static int totalUsed = 0;

	if( commandDone == DONE )
	{
		mcb = system_heap.start;
		totalUsed = 0;
		
		sprintf( pcWriteBuffer, "\r\nРазмер кучи %d байт\r\nАдрес размещения 0x%08x\r\nАдрес первого свободного MCB 0x%08x",
				system_heap.hsize,
				system_heap.start,
				system_heap.freem );
		
		commandDone = HEAPS;
		return pdTRUE;
	}
	
	char type[ 16 ];
	memcpy( type, getMemType( mcb->ts.type ), sizeof( getMemType( mcb->ts.type ) ) );

	if( commandDone == HEAPS )
	{
		sprintf( pcWriteBuffer, "\r\n0x%08x : %05d : %s : 0x%08x",
				mcb->owner,
				mcb->ts.size,
				type,
				mcb->next	);
		
		if ( mcb->ts.type != MARK_FREE )
		{
			totalUsed += mcb->ts.size;
		}
		
		if( mcb->next == system_heap.start )
		{
			commandDone = END;
		}
		else
		{
			mcb = mcb->next;
		}
		
		return pdTRUE;
	}
	
	if( commandDone == END )
	{
		commandDone = DONE;
		
		sprintf( pcWriteBuffer, "\r\nВсего использовано памяти %d байт или %.02f %%", totalUsed,
			( float )( totalUsed ) / ( float )( system_heap.hsize ) * 100.0	);
		
		return pdFALSE;
	}
	
	return pdFALSE;
}