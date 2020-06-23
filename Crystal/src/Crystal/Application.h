#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Crystal
{
	class CR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
#pragma warning( push )
#pragma warning( disable : 4251 )
		std::unique_ptr<Window> m_Window;
#pragma warning( pop )
		bool m_Running = true;
	};

	//Defined by client
	Application* CreateApplication();

}

