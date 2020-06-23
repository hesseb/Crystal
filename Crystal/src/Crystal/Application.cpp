#include "Application.h"

#include "Crystal/Events/ApplicationEvent.h"
#include "Crystal/Log.h"

namespace Crystal {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);

		if (e.IsInCategory(EventCategoryApplication))
		{
			CR_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			CR_TRACE(e);
		}


		while (true);
	}
}
