#pragma once

#include "Crystal/Core.h"
#include "Crystal/Events/Event.h"
#include "Crystal/Core/Timestep.h"

namespace Crystal
{

	class Layer
	{
	public:

		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}

