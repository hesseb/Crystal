#include <crpch.h>
#include "Crystal/Renderer/Renderer2D.h"

#include "Crystal/Renderer/VertexArray.h"
#include "Crystal/Renderer/Shader.h"
#include "Crystal/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Crystal
{

	struct Renderer2DStorage
	{
		Ref<VertexArray> vertexArray;
		Ref<Shader> shader;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();
		s_Data->vertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Ref<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
			});

		s_Data->vertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		Ref<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_Data->vertexArray->SetIndexBuffer(squareIB);

		s_Data->shader = Shader::Create("assets/shaders/FlatColor.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->shader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->shader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->shader)->UploadUniformMat4("u_ModelMatrix", glm::mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{

	}

	//Primitives
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->shader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->shader)->UploadUniformFloat4("u_Color", color);

		s_Data->vertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->vertexArray);
	}

}