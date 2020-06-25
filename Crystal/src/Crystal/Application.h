#pragma once

#include "Core.h"
#include "Window.h"
#include "Crystal/Events/Event.h"
#include "Crystal/Events/ApplicationEvent.h"
#include "Crystal/LayerStack.h"

namespace Crystal
{
	class CR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:

		bool OnWindowClose(WindowCloseEvent& e);

		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;

#pragma warning( push )
#pragma warning( disable : 4251 )
		std::unique_ptr<Window> m_Window;
#pragma warning( pop )
	};

	//Defined by client
	Application* CreateApplication();

}

