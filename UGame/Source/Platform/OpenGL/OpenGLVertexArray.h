#pragma once
#include "Renderer/VertexArray.h"

namespace UGame
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		
		void Bind() override;
		void Unbind() override;

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const override;
		std::shared_ptr<IndexBuffer> GetIndexBuffer() const override;

	private:
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
		std::shared_ptr<IndexBuffer> indexBuffer;

		unsigned int Id;
	};
}
