#include "EngineCore.h"

#include <SDL.h>

namespace HE
{
	namespace HyenaEngine
	{
		EngineCore& EngineCore::Instance()
		{
			static EngineCore s_EngineCore;
			return s_EngineCore;
		}

		EngineCore::CEngineCore()
		{
		}


		EngineCore::~CEngineCore()
		{
		}

		void EngineCore::Initialize(ArgsList& listArgs)
		{
			(void)listArgs;

			auto nResult = SDL_Init( 0 ); // Initialize no subsystems yet, the other component will do so on their own
			if (nResult < 0)
			{
				std::string sExceptMessage;
				sExceptMessage += "SDL failed to initialize. SDL_Error: ";
				sExceptMessage += SDL_GetError();
				throw EngineInitializeException(std::move(sExceptMessage));
			}

		}

		void EngineCore::Start()
		{

		}


	}
}
