#pragma once

namespace HE
{
#ifdef _WINDOWS
// Might as well do this substitution on Windows since the arguments are the same
#define HE_vsnprintf vsnprintf_s
#define HE_noexcept
#define PATH_SEPARATOR "\\"
#ifdef WIN64
#define PLATFORM_WIN64
	using uint8 = unsigned char;
	using int8 = signed char;
	using uint16 = unsigned short;
	using int16 = short;
	using uint32 = unsigned;
	using int32 = int;
	using uint64 = unsigned long long;
	using int64 = long long;
	using size_t = uint64;
#endif // WIN64
#endif // _WINDOWS
	enum class PlatformID : uint8 { Windows64 } ;

	struct PlatformWin64
	{
		static const PlatformID ID = PlatformID::Windows64;
			
	};

#ifdef PLATFORM_WIN64
	using CurrentPlatform = PlatformWin64;
#endif
}