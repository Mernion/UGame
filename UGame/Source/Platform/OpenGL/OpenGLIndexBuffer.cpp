#include "OpenGLIndexBuffer.h"
#include "glad/glad.h"

namespace UGame
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* data, size_t size)
	{
		glCreateBuffers(1, &bufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

		count = size / sizeof(float);
	}

	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
	}

	void OpenGLIndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	size_t OpenGLIndexBuffer::GetCount() const
	{
		return count;
	}


	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &bufferId);
	}

}
