#pragma once

#include <memory>
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"

namespace UGame
{
	class VertexArray
	{
	public:
		static VertexArray* Create();

		virtual void Bind()  = 0;
		virtual void Unbind() = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;
		
		virtual ~VertexArray() = default;
	};
}