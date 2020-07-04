#include <crpch.h>
#include "Crystal/Core/Window.h"

#ifdef CR_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Crystal
{

	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef CR_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
		#else
		CR_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
		#endif
	}

}