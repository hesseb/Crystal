#pragma once

#include <glm/glm.hpp>

namespace Crystal
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float leftBound, float rightBound, float bottomBound, float topBound);

		inline const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		inline float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		inline float GetZoom() const { return m_Zoom; }
		void SetZoom(float zoom) { m_Zoom = zoom > 0.05f ? zoom : 0.05f; RecalculateProjectionMatrix();}

		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();
		void RecalculateProjectionMatrix();

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;

		float m_Zoom = 1.0f;

		glm::vec4 m_Bounds;
	};
}