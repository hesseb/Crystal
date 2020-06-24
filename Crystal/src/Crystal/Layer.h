#pragma once

#include "Crystal/Core.h"
#include "Crystal/Events/Event.h"

namespace Crystal
{

	class CR_API Layer
	{
	public:

		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
#pragma warning( push )
#pragma warning( disable : 4251 )
		std::string m_DebugName;
#pragma warning( pop )
	};
}

