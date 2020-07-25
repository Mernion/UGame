#pragma once

#include "RendererAPI.h"

namespace UGame
{
	class UGAME_API RenderCommand
	{
	public:

		static void SetClearColor(const glm::vec4& color)
		{
			rendererAPI->SetClearColor(color);
		}

		static void Clear()
		{
			rendererAPI->Clear();
		}

		static void Init()
		{
			rendererAPI->Init();
		}

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			rendererAPI->SetViewport(x, y, width, height);
		}

		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			rendererAPI->DrawIndexed(vertexArray);
		}

	private:
		static RendererAPI* rendererAPI;
	};
}