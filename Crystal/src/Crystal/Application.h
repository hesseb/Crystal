#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

namespace Crystal
{
	class CR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

	private:

		bool OnWindowClose(WindowCloseEvent& e);

		bool m_Running = true;

#pragma warning( push )
#pragma warning( disable : 4251 )
		std::unique_ptr<Window> m_Window;
#pragma warning( pop )
	};

	//Defined by client
	Application* CreateApplication();

}

