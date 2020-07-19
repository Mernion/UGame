#pragma once

#include "RendererAPI.h"
#include "Shader.h"

namespace UGame
{
	class OrthographicCamera;

	class UGAME_API Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader> shader);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 viewProjectionMatrix;
		};

		static SceneData* sceneData;
	};
}
