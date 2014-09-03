#include <iostream>
#include <forward_list>

#include <SDL.h>

#include "Platform.h"
#include "EngineCore.h"



namespace HE 
{ 
	namespace HyenaEngine
	{
		// Common entry for all platforms, after their particular initialization
		int32 EngineEntry(ArgsList& listArgs)
		{
			// An abstract proxy from the Engine module
			auto& rEngineCore = EngineCore::Instance();

			// Recursive initialization of all modules.
			try
			{
				rEngineCore.Initialize(listArgs);
			}
			catch (EngineInitializeException& e)
			{
				std::cout << "Engine failed to initialize:" << std::endl << "\t" << e.what() << std::endl;
				return -1;
			}

			// Args should all be parsed now
			listArgs.clear();

			// Program start and execution
			// The engine should clean itself before returning
			try
			{
				rEngineCore.Start();
			}
			catch (EngineRuntimeException& e)
			{
				std::cout << "Engine could not handle a runtime exception:" << std::endl << "\t" << e.what() << std::endl;
				return -1;
			}

			return 0;
		}
	} 
}

int main(int argc, char* argv[])
{
	// Build a list of args that are going to be passed to the other modules
	// When a module finds an arg it can handle, it should do so and then remove it from the list
	HE::HyenaEngine::ArgsList listArgs;
	
	// Inserting the args backward so the first one is in the front
	for (int i = argc; i-- > 0;)
	{
		std::string sCurrentArg{argv[i]};
		listArgs.emplace_front(sCurrentArg);
	}

	auto nResult = HE::HyenaEngine::EngineEntry(listArgs);
	return nResult;
}