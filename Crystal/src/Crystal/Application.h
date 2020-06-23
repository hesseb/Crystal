#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Crystal
{
	class CR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//Defined by client
	Application* CreateApplication();

}

