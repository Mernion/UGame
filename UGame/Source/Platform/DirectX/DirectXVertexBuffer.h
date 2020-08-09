#pragma once
#include "Renderer/VertexBuffer.h"
#include "Renderer/BufferLayout.h"

namespace UGame
{
	class DirectXVertexBuffer : public VertexBuffer
	{
	public:
		void Bind() override;
		void Unbind() override;

		const BufferLayout& GetLayout() const override { return layout; }
		void SetLayout(const BufferLayout& layout) override { this->layout = layout; }

		DirectXVertexBuffer(float* data, size_t size);
		~DirectXVertexBuffer();

	private:
		ID3D11Buffer* vertex_buffer_ptr = nullptr;
		BufferLayout layout;
	};
}
