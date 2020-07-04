#include "ExampleLayer.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


ExampleLayer::ExampleLayer()
	: Layer("Example"), m_CameraController(16.0f / 9.0f, true)
{
	//======== Triangle VA 1 ==============
	m_TriangleVertexArray = Crystal::VertexArray::Create();

	float triangleVertices[3 * 7] = {
		-0.75f, -0.75f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
			0.75f, -0.75f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.0f,   0.75f, 0.0f, 0.2f, 0.8f, 0.8f, 1.0f
	};

	Crystal::Ref<Crystal::VertexBuffer> triangleVertexBuffer
		= Crystal::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices));
	Crystal::BufferLayout layout = {
		{ Crystal::ShaderDataType::Float3, "a_Position" },
		{ Crystal::ShaderDataType::Float4, "a_Color" }
	};
	triangleVertexBuffer->SetLayout(layout);

	uint32_t triangleIndices[3] = { 0, 1, 2 };
	Crystal::Ref<Crystal::IndexBuffer> triangleIndexBuffer
		= Crystal::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t));

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

	Crystal::Ref<Crystal::VertexBuffer> squareVB
		= Crystal::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({
		{ Crystal::ShaderDataType::Float3, "a_Position" }
		});


	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Crystal::Ref<Crystal::IndexBuffer> squareIB
		= Crystal::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

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

	Crystal::Ref<Crystal::VertexBuffer> texVB
		= Crystal::VertexBuffer::Create(texVertices, sizeof(texVertices));
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

	texShader->Bind();
	texShader->SetInt("u_Texture", 0);
}

void ExampleLayer::OnAttach()
{
}

void ExampleLayer::OnDetach()
{
}

void ExampleLayer::OnUpdate(Crystal::Timestep time)
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

	m_FlatColorShader->Bind();
	m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);


	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos(x * 0.055f - 0.5f, y * 0.055f - 0.5f, 0.0f);
			glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), pos) * scale;

			Crystal::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, modelMatrix);
		}
	}

	auto texShader = m_ShaderLibrary.Get("Texture");

	m_Texture->Bind();
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), { -1.0f, 0.0f, 0.0f }) * scale;
	Crystal::Renderer::Submit(texShader, m_TexVertexArray, modelMatrix);
	m_PixelTexture->Bind();
	Crystal::Renderer::Submit(texShader, m_TexVertexArray, modelMatrix);


	modelMatrix = glm::rotate(glm::translate(glm::mat4(1.0f), m_TrianglePosition), m_TriangleRotation, { 0.0f, 0.0f, 1.0f }) * scale;

	Crystal::Renderer::Submit(m_TriangleShader, m_TriangleVertexArray, modelMatrix);

	Crystal::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void ExampleLayer::OnEvent(Crystal::Event& e)
{
	m_CameraController.OnEvent(e);
}