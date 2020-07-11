#pragma once
#include "Renderer/VertexBuffer.h"

namespace UGame
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		void Bind() override;
		void Unbind() override;

		OpenGLVertexBuffer(float* data, size_t size);
		~OpenGLVertexBuffer();

	private:
		
		unsigned int bufferId;
	};
}
