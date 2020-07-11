#pragma once
#include "Renderer/IndexBuffer.h"

namespace UGame
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:

		OpenGLIndexBuffer(unsigned int* data, size_t size);
		
		void Bind() override;
		void Unbind() override;
		size_t GetCount() const override;
		~OpenGLIndexBuffer();

	private:
		
		unsigned int bufferId;

		size_t count;
	};
}
