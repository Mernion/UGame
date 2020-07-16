#include "IndexBuffer.h"
#include "Renderer.h"
#include "UGame/Core.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace UGame
{
	IndexBuffer* IndexBuffer::Create(unsigned int* data, size_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
            UG_CORE_ASSERT(false, "Not Implemented renderer used");
			return nullptr;
			break;
		case RendererAPI::API::OpenGL:
            return new OpenGLIndexBuffer(data, size);
			break;
		}

		UG_CORE_ASSERT(false, "Not implemented renderer used");
		return nullptr;

	}
}