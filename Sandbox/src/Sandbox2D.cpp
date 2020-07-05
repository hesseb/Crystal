#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(16.0f / 9.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	CR_PROFILE_FUNCTION();

	m_CheckerboardTexture = Crystal::Texture2D::Create("assets/textures/Checkerboard.png");
	m_SpriteTexture = Crystal::Texture2D::Create("assets/textures/head.png");
}

void Sandbox2D::OnDetach()
{
	CR_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Crystal::Timestep ts)
{
	CR_PROFILE_FUNCTION();

	//Update
	m_CameraController.OnUpdate(ts);

	{
		CR_PROFILE_SCOPE("Renderer Prep");
		//Render
		Crystal::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Crystal::RenderCommand::Clear();
	}

	{
		int side = 50;
		CR_PROFILE_SCOPE("Renderer Draw");
		Crystal::Renderer2D::BeginScene(m_CameraController.GetCamera());

		for (int j = 0; j < side; j++)
		{
			for (int i = 0; i < side; i++)
			{
				Crystal::Renderer2D::DrawQuad({ (float)i * 0.12f - 2.0f, (float)j * 0.12f - 2.0f, -0.2f }, { 0.1f, 0.1f },
					{i * 1.0f/side, j * 1.0f/side, 0.5f, 1.0f});
			}
		}
		Crystal::Renderer2D::DrawQuad({ 0.0f, 2.1f }, { 1.0f, 1.0f }, m_SquareColorB);
		Crystal::Renderer2D::DrawQuad({ 2.1f, 0.0f }, { 1.0f, 1.0f }, m_SquareColorA);
		Crystal::Renderer2D::DrawQuad({ -5.0f, -0.5f, -0.1f }, { 1.0f, 1.0f }, m_SpriteTexture, 1.0f);
		Crystal::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_SquareColorA);
		Crystal::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.3f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		Crystal::Renderer2D::DrawQuad({ -0.5f, -0.5f, -0.1f }, { 1.0f, 1.0f }, m_SpriteTexture, 1.0f);
		Crystal::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	CR_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square A Color", glm::value_ptr(m_SquareColorA));
	ImGui::ColorEdit4("Square B Color", glm::value_ptr(m_SquareColorB));
	ImGui::End();
}

void Sandbox2D::OnEvent(Crystal::Event& e)
{
	m_CameraController.OnEvent(e);
}