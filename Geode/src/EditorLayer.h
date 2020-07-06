#pragma once

#include <Crystal.h>

namespace Crystal
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;

	private:
		OrthographicCameraController m_CameraController;

		//Temp
		Ref<VertexArray> m_SquareVA;
		Ref<Texture2D> m_CheckerboardTexture;
		Ref<Texture2D> m_SpriteTexture;
		Ref<Framebuffer> m_Framebuffer;

		bool m_ViewportFocused = false, m_ViewportHovered = false;

		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		glm::vec4 m_QuadColorA = { 0.8f, 0.2f, 0.3f, 1.0f };
		glm::vec4 m_QuadColorB = { 0.3f, 0.2f, 0.8f, 1.0f };
	};
}