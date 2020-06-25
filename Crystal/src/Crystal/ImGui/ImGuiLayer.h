#pragma once

#include "Crystal/Layer.h"

#include "Crystal/Events/ApplicationEvent.h"
#include "Crystal/Events/KeyEvent.h"
#include "Crystal/Events/MouseEvent.h"

namespace Crystal
{
	class CR_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}