#ifndef SYS_CLOCK_HPP
#define SYS_CLOCK_HPP

#include <stdint.h>

#ifdef __cplusplus
namespace HS_XT
{
    enum name
    {
        HSI,
        HSE,
    };
}

class CSysClock
{
	private:

	
	public:
          static int init(HS_XT::name source_clock);
};
#endif // __cplusplus


#endif
