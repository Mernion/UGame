#include "Texture.h"
#include "Renderer.h"
#include "UGame/Core.h"
#include <memory>
#include "Platform/OpenGL/OpenGLTexture.h"

namespace UGame
{
	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UG_CORE_ASSERT(false, "Not Implemented renderer used");
			return nullptr;
			break;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
			break;
		}

		UG_CORE_ASSERT(false, "Not implemented renderer used");
		return nullptr;
	}

}