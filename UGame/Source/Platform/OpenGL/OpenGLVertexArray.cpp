#include "Platform/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>
#include "Renderer/IndexBuffer.h"
#include "Renderer/BufferLayout.h"

namespace UGame
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case UGame::ShaderDataType::Float:	return GL_FLOAT;
			case UGame::ShaderDataType::Float2:	return GL_FLOAT;
			case UGame::ShaderDataType::Float3:	return GL_FLOAT;
			case UGame::ShaderDataType::Float4: return GL_FLOAT;
			case UGame::ShaderDataType::Mat3:	return GL_FLOAT;
			case UGame::ShaderDataType::Mat4:	return GL_FLOAT;
			case UGame::ShaderDataType::Int:	return GL_FLOAT;
			case UGame::ShaderDataType::Int2:	return GL_FLOAT;
			case UGame::ShaderDataType::Int3:	return GL_FLOAT;
			case UGame::ShaderDataType::Int4:	return GL_FLOAT;
			case UGame::ShaderDataType::Bool:	return GL_BOOL;
		}

		UG_CORE_ASSERT(false, "Uknown data type");
		return 0;
	}
	
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &Id);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &Id);
	}


	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(Id);
	}

	void OpenGLVertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		Bind();
		vertexBuffer->Bind();

		unsigned int index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : vertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.offset);
			index++;
		}
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(Id);
		indexBuffer->Bind();

		this->indexBuffer = indexBuffer;
	}

	std::shared_ptr<IndexBuffer> OpenGLVertexArray::GetIndexBuffer() const
	{
		return indexBuffer;
	}

	std::vector<std::shared_ptr<VertexBuffer>> OpenGLVertexArray::GetVertexBuffers() const
	{
		return vertexBuffers;
	}


}
