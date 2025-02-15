#include <crpch.h>
#include "Crystal/Renderer/Buffer.h"

#include "Crystal/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Crystal
{
	//================ Vertex Buffer =====================
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CR_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(size);
		}

		CR_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CR_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		CR_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}

	//================ Index Buffer =====================
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CR_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLIndexBuffer>(indices, count);
		}

		CR_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
}