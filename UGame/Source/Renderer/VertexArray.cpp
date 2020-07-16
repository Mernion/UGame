#include "VertexArray.h"


#include "Platform/OpenGL/OpenGLVertexArray.h"

#include "Renderer/Renderer.h"
#include "UGame/Core.h"

namespace UGame
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			UG_CORE_ASSERT(false, "Not Implemented renderer used");
			return nullptr;
			break;
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
			break;
		}

		UG_CORE_ASSERT(false, "Not implemented renderer used");
		return nullptr;

	}

}
