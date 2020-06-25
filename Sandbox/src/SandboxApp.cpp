#include <Crystal.h>

class ExampleLayer : public Crystal::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		if (Crystal::Input::IsKeyPressed(CR_KEY_TAB))
			CR_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(Crystal::Event& event) override
	{
		if (event.GetEventType() == Crystal::EventType::KeyPressed)
		{
			Crystal::KeyPressedEvent& e = (Crystal::KeyPressedEvent&)event;

			if (e.GetKeyCode() == CR_KEY_TAB)
				CR_TRACE("Tab key is pressed (event)!)");

			CR_TRACE("{0}", (char)e.GetKeyCode());
		}
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