#pragma once
#include "RenderCommand.h"
#include "RendererAPI.h"

namespace UGame
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);


		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }


	};
}
