#include <Crystal.h>
#include <Crystal/Core/EntryPoint.h>
//==================================

#include "Sandbox2D.h"
#include "Platform/OpenGL/OpenGLShader.h"


#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Crystal::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(16.0f / 9.0f, true)
	{
		//======== Triangle VA 1 ==============
		m_TriangleVertexArray = Crystal::VertexArray::Create();

		float triangleVertices[3 * 7] = {
			-0.75f, -0.75f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
			 0.75f, -0.75f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.0f,   0.75f, 0.0f, 0.2f, 0.8f, 0.8f, 1.0f
		};

		Crystal::Ref<Crystal::VertexBuffer> triangleVertexBuffer;
		triangleVertexBuffer =  Crystal::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices));
		Crystal::BufferLayout layout = {
			{ Crystal::ShaderDataType::Float3, "a_Position" },
			{ Crystal::ShaderDataType::Float4, "a_Color" }
		};
		triangleVertexBuffer->SetLayout(layout);

		uint32_t triangleIndices[3] = { 0, 1, 2 };
		Crystal::Ref<Crystal::IndexBuffer> triangleIndexBuffer;
		triangleIndexBuffer = Crystal::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t));

		m_TriangleVertexArray->AddVertexBuffer(triangleVertexBuffer);
		m_TriangleVertexArray->SetIndexBuffer(triangleIndexBuffer);


		//======== Square VA 2 ==============
		m_SquareVertexArray = Crystal::VertexArray::Create();

		float squareVertices[3 * 4] = {
			-0.5, -0.5, 0.0f,
			 0.5, -0.5, 0.0f,
			 0.5,  0.5, 0.0f,
			-0.5,  0.5, 0.0f
		};

		Crystal::Ref<Crystal::VertexBuffer> squareVB;
		squareVB = Crystal::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Crystal::ShaderDataType::Float3, "a_Position" }
		});


		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Crystal::Ref<Crystal::IndexBuffer> squareIB;
		squareIB = Crystal::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

		m_SquareVertexArray->AddVertexBuffer(squareVB);
		m_SquareVertexArray->SetIndexBuffer(squareIB);

		//======== Texture VA 3 ==============
		m_TexVertexArray = Crystal::VertexArray::Create();

		float texVertices[5 * 4] = {
			-0.5, -0.5, 0.0f, 0.0f, 0.0f,
			 0.5, -0.5, 0.0f, 1.0f, 0.0f,
			 0.5,  0.5, 0.0f, 1.0f, 1.0f,
			-0.5,  0.5, 0.0f, 0.0f, 1.0f
		};

		Crystal::Ref<Crystal::VertexBuffer> texVB;
		texVB = Crystal::VertexBuffer::Create(texVertices, sizeof(texVertices));
		texVB->SetLayout({
			{ Crystal::ShaderDataType::Float3, "a_Position" },
			{ Crystal::ShaderDataType::Float2, "a_TexCoord" }
		});

		//Crystal::Ref<Crystal::IndexBuffer> squareIB;
		//squareIB.reset(Crystal::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		m_TexVertexArray->AddVertexBuffer(texVB);
		m_TexVertexArray->SetIndexBuffer(squareIB);

		//=========== Shaders ==============
		m_TriangleShader = Crystal::Shader::Create("assets/shaders/Triangle.glsl");
		m_FlatColorShader = Crystal::Shader::Create("assets/shaders/FlatColor.glsl");
		auto texShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		//=========== Textures =============
		m_Texture = Crystal::Texture2D::Create("assets/textures/Checkerboard.png");
		m_PixelTexture = Crystal::Texture2D::Create("assets/textures/head.png");

		std::dynamic_pointer_cast<Crystal::OpenGLShader>(texShader)->Bind();
		std::dynamic_pointer_cast<Crystal::OpenGLShader>(texShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Crystal::Timestep time) override
	{

		m_CameraController.OnUpdate(time);

		float ts = (float)time;

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

		if (Crystal::Input::IsKeyPressed(CR_KEY_P))
		{
			m_TrianglePosition = { 0.0f, 0.0f, 0.0f };
			m_TriangleRotation = 0.0f;
		}

		Crystal::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Crystal::RenderCommand::Clear();

		Crystal::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f));

		std::dynamic_pointer_cast<Crystal::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Crystal::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);


		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.055f -0.5f, y * 0.055f - 0.5f, 0.0f);
				glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), pos) * scale;

				Crystal::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, modelMatrix);
			}
		}

		auto texShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
		glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), {-1.0f, 0.0f, 0.0f}) * scale;
		Crystal::Renderer::Submit(texShader, m_TexVertexArray, modelMatrix);
		m_PixelTexture->Bind();
		Crystal::Renderer::Submit(texShader, m_TexVertexArray, modelMatrix);


		modelMatrix = glm::rotate(glm::translate(glm::mat4(1.0f), m_TrianglePosition), m_TriangleRotation, { 0.0f, 0.0f, 1.0f }) * scale;

		Crystal::Renderer::Submit(m_TriangleShader, m_TriangleVertexArray, modelMatrix);

		Crystal::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Crystal::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

	private:
		Crystal::OrthographicCameraController m_CameraController;
		Crystal::ShaderLibrary m_ShaderLibrary;

		Crystal::Ref<Crystal::Shader> m_TriangleShader;
		Crystal::Ref<Crystal::VertexArray> m_TriangleVertexArray;

		Crystal::Ref<Crystal::Shader> m_FlatColorShader;
		Crystal::Ref<Crystal::VertexArray> m_SquareVertexArray;

		//Crystal::Ref<Crystal::Shader> m_TexShader;
		Crystal::Ref<Crystal::VertexArray> m_TexVertexArray;
		Crystal::Ref<Crystal::Texture2D> m_Texture;
		Crystal::Ref<Crystal::Texture2D> m_PixelTexture;

		glm::vec3 m_TrianglePosition = { 0.0f, 0.0f, 0.0f };
		float m_TriangleMoveSpeed = 2.0f;

		float m_TriangleRotation = 0.0f;
		float m_TriangleRotationSpeed = 2.0f;

		glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};


class Sandbox : public Crystal::Application
{
public:
	Sandbox()
	{
		//PushLayer(Crystal::CreateRef<ExampleLayer>());
		PushLayer(Crystal::CreateRef<Sandbox2D>());
	}

	~Sandbox() = default;
};

Crystal::Application* Crystal::CreateApplication()
{
	return new Sandbox();
}