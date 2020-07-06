#include <Crystal.h>
#include <Crystal/Core/EntryPoint.h>
//==================================

#include "EditorLayer.h"

namespace Crystal
{
	class Geode : public Application
	{
	public:
		Geode()
			: Application("Geode Editor")
		{
			PushLayer(CreateRef<EditorLayer>());
		}

		~Geode() = default;
	};

	Application* CreateApplication()
	{
		return new Geode();
	}
}