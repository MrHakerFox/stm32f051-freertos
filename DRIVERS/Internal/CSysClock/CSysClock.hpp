#ifndef SYS_CLOCK_HPP
#define SYS_CLOCK_HPP

#include <stdint.h>

enum TSysClockType
{
	HSI,
	HSE,
};


#ifdef __cplusplus
class CSysClock
{
	private:

	
	public:
          static int init( TSysClockType source_clock);
};

extern "C" int cSysClockWrapper( TSysClockType source );
#endif // __cplusplus


#endif
