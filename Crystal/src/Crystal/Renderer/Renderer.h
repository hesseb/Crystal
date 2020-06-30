#pragma once

#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"

namespace Crystal
{
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader,
			const std::shared_ptr<VertexArray>& vertexArray,
			const glm::mat4& modelMatrix = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI(){ return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;

		};

		static SceneData* s_SceneData;
	};
}