#pragma once

#include <memory>
#include <vector>

#include "IndexBuffer.h"
#include "Renderer/VertexBuffer.h"


namespace UGame
{
	class UGAME_API VertexArray
	{
	public:
		static VertexArray* Create();

		virtual void Bind()  = 0;
		virtual void Unbind() = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const = 0;
		virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() const = 0;

		
		virtual ~VertexArray() = default;
	};
}