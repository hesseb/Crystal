#include <crpch.h>
#include "Crystal/Renderer/Framebuffer.h"

#include "Crystal/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Crystal
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CR_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLFramebuffer>(spec);
		}

		CR_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}
