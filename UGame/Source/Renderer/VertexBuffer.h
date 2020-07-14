#pragma once
#include "Renderer/BufferLayout.h"

namespace UGame
{
	class VertexBuffer
	{
	public:
		static VertexBuffer* Create(float* data, size_t size);

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		virtual ~VertexBuffer() {};
	};
}