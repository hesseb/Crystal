#include <Crystal.h>

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Crystal::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-3.2f, 3.2f, -1.8f, 1.8f), m_CameraPosition({ 0.0f, 0.0f, 0.0f })
	{
		//======== VA 1 ==============
		m_VertexArray.reset(Crystal::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.75f, -0.75f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
			 0.75f, -0.75f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.0f,   0.75f, 0.0f, 0.2f, 0.8f, 0.8f, 1.0f
		};

		std::shared_ptr<Crystal::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Crystal::VertexBuffer::Create(vertices, sizeof(vertices)));
		Crystal::BufferLayout layout = {
			{ Crystal::ShaderDataType::Float3, "a_Position" },
			{ Crystal::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Crystal::IndexBuffer> indexBuffer;
		indexBuffer.reset(Crystal::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);


		//======== VA 2 ==============
		m_SquareVertexArray.reset(Crystal::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5, -0.5, 0.0f,
			 0.5, -0.5, 0.0f,
			 0.5,  0.5, 0.0f,
			-0.5,  0.5, 0.0f
		};

		std::shared_ptr<Crystal::VertexBuffer> squareVB;
		squareVB.reset(Crystal::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Crystal::ShaderDataType::Float3, "a_Position" }
			});


		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Crystal::IndexBuffer> squareIB;
		squareIB.reset(Crystal::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		m_SquareVertexArray->AddVertexBuffer(squareVB);
		m_SquareVertexArray->SetIndexBuffer(squareIB);

		//=========== Shaders ==============

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_ModelMatrix;

			out vec4 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;
				v_Position = u_ModelMatrix * vec4(a_Position, 1.0);
				gl_Position = u_ViewProjection * v_Position;
				//u_ModelMatrix * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec4 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5);
				//color = v_Color;
			}
		)";

		m_Shader.reset(Crystal::Shader::Create(vertexSrc, fragmentSrc));


		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_ModelMatrix;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_ModelMatrix * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.3, 0.2, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(Crystal::Shader::Create(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(Crystal::Timestep time) override
	{
		//if (Crystal::Input::IsKeyPressed(CR_KEY_TAB))
		//	CR_TRACE("Tab key is pressed (poll)!");

		float ts = (float)time;

		if (Crystal::Input::IsKeyPressed(CR_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Crystal::Input::IsKeyPressed(CR_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Crystal::Input::IsKeyPressed(CR_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Crystal::Input::IsKeyPressed(CR_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Crystal::Input::IsKeyPressed(CR_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Crystal::Input::IsKeyPressed(CR_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		if (Crystal::Input::IsKeyPressed(CR_KEY_J))
			m_TrianglePosition.x -= m_TriangleMoveSpeed * ts;
		else if (Crystal::Input::IsKeyPressed(CR_KEY_L))
			m_TrianglePosition.x += m_TriangleMoveSpeed * ts;

		if (Crystal::Input::IsKeyPressed(CR_KEY_I))
			m_TrianglePosition.y += m_TriangleMoveSpeed * ts;
		else if (Crystal::Input::IsKeyPressed(CR_KEY_K))
			m_TrianglePosition.y -= m_TriangleMoveSpeed * ts;

		if (Crystal::Input::IsKeyPressed(CR_KEY_U))
			m_TriangleRotation += m_TriangleRotationSpeed * ts;
		else if (Crystal::Input::IsKeyPressed(CR_KEY_O))
			m_TriangleRotation -= m_TriangleRotationSpeed * ts;

		if (Crystal::Input::IsKeyPressed(CR_KEY_R))
		{
			m_CameraPosition = { 0.0f, 0.0f, 0.0f };
			m_CameraRotation = 0.0f;
			m_CameraZoom = 1.0f;
			m_Camera.SetZoom(m_CameraZoom);
		}

		if (Crystal::Input::IsKeyPressed(CR_KEY_P))
		{
			m_TrianglePosition = { 0.0f, 0.0f, 0.0f };
			m_TriangleRotation = 0.0f;
		}

		Crystal::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Crystal::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Crystal::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f - 1.0f, y * 0.11f - 1.0f, 0.0f);
				glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), pos) * scale;

				Crystal::Renderer::Submit(m_BlueShader, m_SquareVertexArray, modelMatrix);
			}
		}

		glm::mat4 modelMatrix = glm::rotate(glm::translate(glm::mat4(1.0f), m_TrianglePosition), m_TriangleRotation, { 0.0f, 0.0f, 1.0f });

		Crystal::Renderer::Submit(m_Shader, m_VertexArray, modelMatrix);

		Crystal::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		//ImGui::Begin("Test");
		//ImGui::Text("Mar sucks");
		//ImGui::End();
	}

	void OnEvent(Crystal::Event& event) override
	{
		if (event.GetEventType() == Crystal::EventType::MouseScrolled)
		{
			Crystal::MouseScrolledEvent& e = (Crystal::MouseScrolledEvent&)event;

			if (e.GetYOffset() == 1)
				m_CameraZoom -= m_CameraZoomSpeed;
			if (e.GetYOffset() == -1)
				m_CameraZoom += m_CameraZoomSpeed;

			if (m_CameraZoom < 0.2f)
				m_CameraZoom = 0.2f;
			else if (m_CameraZoom > 1.8f)
				m_CameraZoom = 1.8f;

			m_Camera.SetZoom(m_CameraZoom);
		}
	}

	private:
		std::shared_ptr<Crystal::Shader> m_Shader;
		std::shared_ptr<Crystal::VertexArray> m_VertexArray;

		std::shared_ptr<Crystal::Shader> m_BlueShader;
		std::shared_ptr<Crystal::VertexArray> m_SquareVertexArray;

		Crystal::OrthographicCamera m_Camera;
		glm::vec3 m_CameraPosition;
		float m_CameraMoveSpeed = 5.0f;

		float m_CameraRotation = 0.0f;
		float m_CameraRotationSpeed = 180.0f;

		float m_CameraZoom = 1.0f;
		float m_CameraZoomSpeed = 0.1f;

		glm::vec3 m_TrianglePosition = { 0.0f, 0.0f, 0.0f };
		float m_TriangleMoveSpeed = 2.0f;

		float m_TriangleRotation = 0.0f;
		float m_TriangleRotationSpeed = 2.0f;

};


class Sandbox : public Crystal::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Crystal::Application* Crystal::CreateApplication()
{
	return new Sandbox();
}