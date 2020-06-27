#pragma once

#ifdef WIN32
	#ifdef UG_BUILD_DLL
	#define UGAME_API __declspec(dllexport)
	#else
	#define UGAME_API __declspec(dllimport)
	#endif
#else
	#error UGame only supports Windows!
#endif

#ifdef UG_ENABLE_ASSERTS
	#define UG_ASSERT(x, ...) { if (!(x)) { UG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define UG_CORE_ASSERT(x, ...) {if !((x)) {UG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define UG_ASSERT(x, ...)
	#define UG_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << (x))