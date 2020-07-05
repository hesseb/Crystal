#pragma once

#include "Crystal/Renderer/Camera.h"
#include "Crystal/Core/Timestep.h"

#include "Crystal/Events/ApplicationEvent.h"
#include "Crystal/Events/MouseEvent.h"

namespace Crystal
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotationEnable = false, bool zoomEnabled = true);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_RotationEnabled;
		bool m_ZoomEnabled;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;   //Degrees, CCW
		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f;
		float m_CameraZoomSpeed = 0.25f;
	};
}