#pragma once

#include "Platform.h"
#include <exception>

namespace HE
{
	namespace SDK
	{
		namespace Assert
		{
			enum class Result { Halt, Continue, Terminate, AlwaysContinue };
			using Handler = Result(*) (const char* sCondition, const char* sMessage, const char* file, int32 line);

			Handler GetHandler();
			void SetHandler(Handler handler);

			Result ReportFailure(const char* sCondition, const char* sFile, int line, const char* msg, ...);
		}
	}
}

#ifdef PLATFORM_WIN64

#define HE_ASSERTS_ENABLED

#if defined(HE_ASSERTS_ENABLED)

#define HE_HALT __debugbreak()
#define HE_TERMINATE std::terminate()
#define HE_ASSERT(condition)																\
	do {																					\
		static bool bAlwaysContinue = false;												\
		if (!bAlwaysContinue)																\
		{																					\
			if (!(condition))																\
			{																				\
				switch ( HE::SDK::Assert::ReportFailure(#condition, __FILE__, __LINE__, nullptr) )	\
				{																			\
				case HE::SDK::Assert::Result::Halt: HE_HALT; break;							\
				case HE::SDK::Assert::Result::Terminate: HE_TERMINATE; break;				\
				case HE::SDK::Assert::Result::AlwaysContinue: bAlwaysContinue = true; break;\
				case HE::SDK::Assert::Result::Continue: break;								\
				}																			\
			}																				\
		} 																					\
	} while (__LINE__ == -1, false)															\

#else
#define HE_ASSERT(condition) \
	do { (void)sizeof(condition); } while( __LINE__ == -1, false)
#endif // HE_ASSERTS_ENABLED

#endif // PLATFORM_WIN64