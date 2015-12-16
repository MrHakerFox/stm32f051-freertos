/**
	\brief The file contains eeror codes
*/



#ifndef RET_VALS_HPP
#define RET_VALS_HPP



enum TRetVal
{
	/** Common result values */
    rvOK                        = 0x00,		/** No eerors during the operation */
    rvFAILED                    = 0x01,    	/** Function completed with general error */
};



#endif