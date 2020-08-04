#include "RendererAPI.h"

namespace UGame
{
#if UG_PLATFORM_WINDOWS
	RendererAPI::API RendererAPI::api = RendererAPI::API::DirectX;
#elif UG_PLATFORM_LINUX
	RendererAPI::API RendererAPI::api = RendererAPI::API::OpenGL;
#endif
}