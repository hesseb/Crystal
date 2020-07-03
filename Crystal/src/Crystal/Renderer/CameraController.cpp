#include <crpch.h>
#include "Crystal/Renderer/CameraController.h"

#include "Crystal/Core/Input.h"
#include "Crystal/Core/KeyCodes.h"

namespace Crystal
{

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotationEnabled, bool zoomEnabled)
		: m_AspectRatio(aspectRatio), m_RotationEnabled(rotationEnabled), m_ZoomEnabled(zoomEnabled),
		m_Camera(m_AspectRatio, m_ZoomLevel)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep time)
	{
		CR_PROFILE_FUNCTION();

		float ts = (float)time;

		if (Input::IsKeyPressed(CR_KEY_A))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(CR_KEY_D))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (Crystal::Input::IsKeyPressed(CR_KEY_W))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y +=  cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;

		}
		else if (Crystal::Input::IsKeyPressed(CR_KEY_S))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -=  cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;

		}

		if (m_RotationEnabled)
		{
			if (Crystal::Input::IsKeyPressed(CR_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			else if (Crystal::Input::IsKeyPressed(CR_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;
		}



		if (Crystal::Input::IsKeyPressed(CR_KEY_R))
		{
			m_CameraPosition = { 0.0f, 0.0f, 0.0f };
			m_CameraRotation = 0.0f;
			if (m_ZoomEnabled)
			{
				m_ZoomLevel = 1.0f;
				m_Camera.SetProjection(m_AspectRatio, m_ZoomLevel);
			}
		}

		if (m_RotationEnabled) m_Camera.SetRotation(m_CameraRotation);

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel * 3;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		CR_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(CR_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(CR_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		CR_PROFILE_FUNCTION();

		if (m_ZoomEnabled)
		{
			m_ZoomLevel -= e.GetYOffset() * m_CameraZoomSpeed;
			m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
			m_ZoomLevel = std::min(m_ZoomLevel, 5.0f);
			m_Camera.SetProjection(m_AspectRatio, m_ZoomLevel);
		}

		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		CR_PROFILE_FUNCTION();

		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(m_AspectRatio, m_ZoomLevel);
		return false;
	}
}