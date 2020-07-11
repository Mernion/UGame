#pragma once
#include "Renderer/IndexBuffer.h"

namespace UGame
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:

		OpenGLIndexBuffer(float* data, size_t count);
		
		void Bind() override;
		void Unbind() override;
	};
}
