#include <crpch.h>
#include "Crystal/Core/Application.h"

#include "Crystal/Core/Log.h"
#include "Crystal/Core/Log.h"
#include "Crystal/Renderer/Renderer.h"
#include "Crystal/Core/Input.h"

namespace Crystal
{

	Application* Application::s_Instance = nullptr;



	Application::Application(const std::string& name)
	{
		CR_PROFILE_FUNCTION();

		CR_CORE_ASSERT(!s_Instance, "Application already exists.");
		s_Instance = this;

		m_Window = Window::Create(WindowProps(name));
		m_Window->SetEventCallback(CR_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = CreateRef<ImGuiLayer>();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		CR_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::PushLayer(Ref<Layer> layer)
	{
		CR_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Ref<Layer> overlay)
	{
		CR_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnEvent(Event& e)
	{
		CR_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(CR_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(CR_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			if (e.Handled) break;

			(*--it)->OnEvent(e);

		}
	}

	void Application::Run()
	{
		CR_PROFILE_FUNCTION();

		while (m_Running)
		{
			CR_PROFILE_SCOPE("RunLoop");

			double time = Timestep::GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				CR_PROFILE_SCOPE("LayerStack OnUpdate");

				for (Ref<Layer> layer : m_LayerStack) layer->OnUpdate(timestep);
			}

			m_ImGuiLayer->Begin();
			{
				CR_PROFILE_SCOPE("LayerStack OnImGuiRender");

				for (Ref<Layer> layer : m_LayerStack) layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}

	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		CR_PROFILE_FUNCTION();
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}
