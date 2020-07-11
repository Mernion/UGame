#pragma once

namespace UGame
{
	class VertexBuffer
	{
	public:
		static VertexBuffer* Create(float* data, size_t size);

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual ~VertexBuffer() {};
	};
}