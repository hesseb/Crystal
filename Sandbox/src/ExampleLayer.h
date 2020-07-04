#pragma once

#include <Crystal.h>

class ExampleLayer : public Crystal::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Crystal::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Crystal::Event& e) override;

private:
	Crystal::OrthographicCameraController m_CameraController;
	Crystal::ShaderLibrary m_ShaderLibrary;

	Crystal::Ref<Crystal::Shader> m_TriangleShader;
	Crystal::Ref<Crystal::VertexArray> m_TriangleVertexArray;

	Crystal::Ref<Crystal::Shader> m_FlatColorShader;
	Crystal::Ref<Crystal::VertexArray> m_SquareVertexArray;

	Crystal::Ref<Crystal::VertexArray> m_TexVertexArray;
	Crystal::Ref<Crystal::Texture2D> m_Texture;
	Crystal::Ref<Crystal::Texture2D> m_PixelTexture;

	glm::vec3 m_TrianglePosition = { 0.0f, 0.0f, 0.0f };
	float m_TriangleMoveSpeed = 2.0f;

	float m_TriangleRotation = 0.0f;
	float m_TriangleRotationSpeed = 2.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};