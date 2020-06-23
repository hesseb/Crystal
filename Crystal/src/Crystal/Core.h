#pragma once

#ifdef CR_PLATFORM_WINDOWS
	#ifdef CR_BUILD_DLL
		#define CR_API __declspec(dllexport)
	#else
		#define CR_API __declspec(dllimport)
	#endif
#else
		#error Crystal only supports Windows!
#endif

#define BIT(x) (1 << x)