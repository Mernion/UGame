#pragma once

#ifdef UG_PLATFORM_WINDOWS
	#ifdef UG_BUILD_DLL
	#define UGAME_API __declspec(dllexport)
	#else
	#define UGAME_API __declspec(dllimport)
	#endif
#else
	#error UGame only supports Windows!
#endif

#define BIT(x) (1 << (x))