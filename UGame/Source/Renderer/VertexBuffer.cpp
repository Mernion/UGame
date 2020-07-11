#include "VertexBuffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"
#include "UGame/Core.h"

namespace UGame
{
	VertexBuffer* VertexBuffer::Create(float* data, size_t size)
	{
		switch(Renderer::GetAPI())
		{
		case RendererAPI::None:
			UG_CORE_ASSERT(false, "Not Implemented renderer used");
			return nullptr;
			break;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(data, size);
			break;
		}

		UG_CORE_ASSERT(false, "Not implemented renderer used");
		return nullptr;
		
	}
}