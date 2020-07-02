#include <crpch.h>
#include "Crystal/Renderer/RenderCommand.h"

namespace Crystal
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}