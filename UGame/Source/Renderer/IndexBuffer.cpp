#include "IndexBuffer.h"
#include "Renderer.h"
#include "UGame/Core.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace UGame
{
	IndexBuffer* IndexBuffer::Create(float* data, size_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
            UG_CORE_ASSERT(false, "Not Implemented renderer used");
			return nullptr;
			break;
		case RendererAPI::OpenGL:
            return new OpenGLIndexBuffer(data, count);
			break;
		}

		UG_CORE_ASSERT(false, "Not implemented renderer used");
		return nullptr;

	}
}