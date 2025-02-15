#include <crpch.h>
#include "Crystal/Renderer/VertexArray.h"

#include "Crystal/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Crystal
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CR_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexArray>();
		}

		CR_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
}