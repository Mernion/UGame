#pragma once

namespace UGame
{
	class IndexBuffer
	{
	public:
		static IndexBuffer* Create(float* data, size_t count);

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual ~IndexBuffer() {};
	};
}