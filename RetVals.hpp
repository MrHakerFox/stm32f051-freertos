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
	
	rvSETTING_ERROR				= 0x03,		/** Input parameters are incorrect */
	
	rvTIME_OUT					= 0x05,		/** Operation finished with timeout */
};



#endif