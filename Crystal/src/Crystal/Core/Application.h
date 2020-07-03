#pragma once

#include "Crystal/Core/Core.h"
#include "Crystal/Core/Window.h"
#include "Crystal/Core/LayerStack.h"
#include "Crystal/Events/Event.h"
#include "Crystal/Events/ApplicationEvent.h"
#include "Crystal/ImGui/ImGuiLayer.h"

#include "Crystal/Core/Timestep.h"

namespace Crystal
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Ref<Layer> layer);
		void PushOverlay(Ref<Layer> layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		Scope<Window> m_Window;
		Ref<ImGuiLayer> m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		static Application* s_Instance;

		double m_LastFrameTime = 0.0;
	};

	//Defined by client
	Application* CreateApplication();

}

