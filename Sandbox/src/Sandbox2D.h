#pragma once

#include <Crystal.h>

#define PROFILE_SCOPE(name) Crystal::Timer timer##__LINE__(name, [&](Crystal::ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })

class Sandbox2D : public Crystal::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Crystal::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Crystal::Event& e) override;

private:
	Crystal::OrthographicCameraController m_CameraController;

	//Temp
	Crystal::Ref<Crystal::VertexArray> m_SquareVA;
	Crystal::Ref<Crystal::Texture2D> m_CheckerboardTexture;
	Crystal::Ref<Crystal::Texture2D> m_SpriteTexture;
	Crystal::Ref<Crystal::Framebuffer> m_Framebuffer;

	glm::vec4 m_SquareColorA = { 0.8f, 0.2f, 0.3f, 1.0f };
	glm::vec4 m_SquareColorB = { 0.3f, 0.2f, 0.8f, 1.0f };
};