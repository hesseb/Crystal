#include <Crystal.h>
#include <Crystal/Core/EntryPoint.h>
//==================================

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Crystal::Application
{
public:
	Sandbox()
	{
		//PushLayer(Crystal::CreateRef<ExampleLayer>());
		PushLayer(Crystal::CreateRef<Sandbox2D>());
	}

	~Sandbox() = default;
};

Crystal::Application* Crystal::CreateApplication()
{
	return new Sandbox();
}