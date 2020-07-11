#pragma once

namespace UGame
{
	class IndexBuffer
	{
	public:
		static IndexBuffer* Create(unsigned int* data, size_t count);

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual size_t GetCount() const = 0;
		virtual ~IndexBuffer() {};
	};
}