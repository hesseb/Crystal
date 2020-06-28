#pragma once

#include "Core.h"
#include "Window.h"
#include "Crystal/LayerStack.h"
#include "Crystal/Events/Event.h"
#include "Crystal/Events/ApplicationEvent.h"
#include "Crystal/ImGui/ImGuiLayer.h"

#include "Crystal/Renderer/Shader.h"
#include "Crystal/Renderer/Buffer.h"
#include "Crystal/Renderer/VertexArray.h"

namespace Crystal
{
	class CR_API Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:

		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVertexArray;

		static Application* s_Instance;
	};

	//Defined by client
	Application* CreateApplication();

}

