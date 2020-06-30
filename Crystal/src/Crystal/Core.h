#pragma once

#include <memory>

#ifdef CR_PLATFORM_WINDOWS
	#if CR_DYNAMIC_LINK
		#ifdef CR_BUILD_DLL
			#define CR_API __declspec(dllexport)
		#else
			#define CR_API __declspec(dllimport)
		#endif
	#else
		#define CR_API
	#endif
#else
		#error Crystal only supports Windows!
#endif

#ifdef CR_DEBUG
	#define CR_ENABLE_ASSERTS
#endif

#ifdef CR_ENABLE_ASSERTS
	#define CR_ASSERT(x, ...) { if(!(x)) { CR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define CR_CORE_ASSERT(x, ...) { if(!(x)) { CR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CR_ASSERT(x, ...)
	#define CR_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define CR_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Crystal
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}