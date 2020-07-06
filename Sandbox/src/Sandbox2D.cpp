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
	Crystal::Renderer2D::ResetStats();
	{
		CR_PROFILE_SCOPE("Renderer Prep");
		//Render
		Crystal::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Crystal::RenderCommand::Clear();
	}
/*
	{
		int side = 50;
		static float rotation = 0.0f;
		rotation += (float)ts * 50.0f;

		CR_PROFILE_SCOPE("Renderer Draw");

		Crystal::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Crystal::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.6f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		for (int j = 0; j < side; j++)
		{
			for (int i = 0; i < side; i++)
			{
				Crystal::Renderer2D::DrawQuad({ (float)i * 0.12f - 2.0f, (float)j * 0.12f - 2.0f, -0.2f }, { 0.1f, 0.1f },
					{i * 1.0f/side, j * 1.0f/side, 0.5f, 1.0f});
			}
		}
		Crystal::Renderer2D::DrawQuad({ 0.0f, 2.1f }, { 1.0f, 1.0f }, m_SquareColorB);
		Crystal::Renderer2D::DrawQuad({ -5.0f, -0.5f, -0.1f }, { 1.0f, 1.0f }, m_SpriteTexture, 1.0f);
		Crystal::Renderer2D::DrawRotatedQuad({ -0.5f, -0.5f, -0.1f }, { 1.0f, 1.0f }, -45.0f, m_SpriteTexture, 1.0f);
		Crystal::Renderer2D::DrawRotatedQuad({ 2.1f, 0.0f }, { 1.0f, 1.0f }, rotation, m_SquareColorA);
		Crystal::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_SquareColorA);
		Crystal::Renderer2D::EndScene();
	}
*/
	{
		static float rotation = 0.0f;
		rotation += (float)ts * 50.0f;
		CR_PROFILE_SCOPE("Renderer Draw");
		Crystal::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Crystal::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		Crystal::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Crystal::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Crystal::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		Crystal::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		Crystal::Renderer2D::EndScene();

		Crystal::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Crystal::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Crystal::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.1f }, { 1.0f, 1.0f }, rotation, m_SpriteTexture, 1.0f);
		Crystal::Renderer2D::EndScene();
	}


}

void Sandbox2D::OnImGuiRender()
{
	CR_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square A Color", glm::value_ptr(m_SquareColorA));
	ImGui::ColorEdit4("Square B Color", glm::value_ptr(m_SquareColorB));

	auto stats = Crystal::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::Text("Average frametime: %.3f ms (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

void Sandbox2D::OnEvent(Crystal::Event& e)
{
	m_CameraController.OnEvent(e);
}