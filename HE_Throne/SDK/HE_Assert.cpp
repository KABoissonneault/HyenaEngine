#include "HE_Assert.h"
#include "Platform.h"

#include <iostream>
#include <stdarg.h>

namespace HE
{
	namespace SDK
	{
		namespace Assert
		{
			namespace
			{
				Result DefaultHandler(const char* psCondition, const char* psMsg, const char* psFile, const int nLine)
				{
					std::cout << "[" << psFile << "(" << nLine << ") Assert failure: ";
					
					if (psCondition)
					{
						std::cout << psCondition;
					}

					if (psMsg)
					{
						std::cout << psMsg;
					}

					std::cout << std::endl;
					
					return Result::Halt;
				}

				Handler s_pAssertHandler = DefaultHandler;
			}

			Handler GetHandler()
			{
				return s_pAssertHandler;
			}

			void SetHandler(Handler pHandler)
			{
				s_pAssertHandler = pHandler;
			}

			Result ReportFailure(const char* psCondition, const char* psFile, int nLine, const char* psMsg, ...)
			{
				const char* psOutMessage = nullptr;
				if (psMsg)
				{
					const size_t knMessageBufferSize = 1024;
					char sMessageBuffer[knMessageBufferSize];
					{
						va_list args;
						va_start(args, psMsg);
						const auto nSize = _vscprintf(psMsg, args);
						if (nSize < knMessageBufferSize)
						{
							HE_vsnprintf(sMessageBuffer, knMessageBufferSize, psMsg, args);
						}
						va_end(args);
					}

					psOutMessage = &sMessageBuffer[0];
				}

				return s_pAssertHandler(psCondition, psOutMessage, psFile, nLine);
			}
		}
	}
}