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
	m_CheckerboardTexture = Crystal::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Crystal::Timestep ts)
{
	CR_PROFILE_FUNCTION();

	//Update
	{
		CR_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	{
		CR_PROFILE_SCOPE("Renderer Prep");
		//Render
		Crystal::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Crystal::RenderCommand::Clear();
	}

	{
		CR_PROFILE_SCOPE("Renderer Draw");
		Crystal::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Crystal::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_SquareColorA);
		Crystal::Renderer2D::DrawQuad({ 2.1f, 0.0f }, { 1.0f, 1.0f }, m_SquareColorA);
		Crystal::Renderer2D::DrawQuad({ 0.0f, 2.1f, 0.5f }, { 1.0f, 1.0f }, m_SquareColorB);
		Crystal::Renderer2D::DrawQuad({ 0.4f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_SquareColorB);
		Crystal::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.f }, m_CheckerboardTexture);
		Crystal::Renderer::EndScene();
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