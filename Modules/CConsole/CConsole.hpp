#ifndef CCONSOLE_HHP
#define CCONSOLE_HHP


#ifdef __cplusplus
class CConsole
{
	private:
	static CConsole * _self;
	
	
	
	protected:
	
	
	
	public:
	static CConsole * getInstance()
	{
		if( !_self )
		{
			//CConsole myConsole;
			//_self = &myConsole;
		}
		return _self;
	}
	
	void exec();
};


extern "C" void cConsoleWrapper();

#else
void cConsoleWrapper();
#endif



#endif
