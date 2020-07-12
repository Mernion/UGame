#pragma once
#include "Renderer/VertexBuffer.h"
#include "Renderer/BufferLayout.h"

namespace UGame
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		void Bind() override;
		void Unbind() override;

		const BufferLayout& GetLayout() const override { return layout; }
		void SetLayout(const BufferLayout& layout) override { this->layout = layout; }

		OpenGLVertexBuffer(float* data, size_t size);
		~OpenGLVertexBuffer();

	private:
		unsigned int bufferId;
		BufferLayout layout;
	};
}
