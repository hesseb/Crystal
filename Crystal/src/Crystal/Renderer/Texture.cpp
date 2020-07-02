#include <crpch.h>
#include "Crystal/Renderer/Texture.h"

#include "Crystal/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Crystal
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CR_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(path);
		}

		CR_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
}