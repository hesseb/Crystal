#include <crpch.h>
#include "Crystal/Core/Input.h"

#ifdef CR_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsInput.h"
#endif

namespace Crystal {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
		#ifdef CR_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
		#else
		CR_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
		#endif
	}
}