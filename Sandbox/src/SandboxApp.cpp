#include <Crystal.h>

class ExampleLayer : public Crystal::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		//CR_INFO("ExampleLayer::Update");
	}

	void OnEvent(Crystal::Event& event) override
	{
		CR_TRACE("{0}", event);
	}
};


class Sandbox : public Crystal::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Crystal::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Crystal::Application* Crystal::CreateApplication()
{
	return new Sandbox();
}