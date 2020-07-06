#pragma once

#include <memory>

#ifdef CR_PLATFORM_WINDOWS

#else
		#error Crystal only supports Windows!
#endif

#ifdef CR_DEBUG
	#ifdef CR_PLATFORM_WINDOWS
		#define CR_DEBUGBREAK() __debugbreak()
	#elif defined(CR_PLATFORM_LINUX)
		#include <signal.h>
		#define CR_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define CR_ENABLE_ASSERTS
#else
	#define CR_DEBUGBREAK()
#endif

#ifdef CR_ENABLE_ASSERTS
	#define CR_ASSERT(x, ...) { if(!(x)) { CR_ERROR("Assertion Failed: {0}", __VA_ARGS__); CR_DEBUGBREAK(); }}
	#define CR_CORE_ASSERT(x, ...) { if(!(x)) { CR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); CR_DEBUGBREAK(); } }
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
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}