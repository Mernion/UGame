#include "RenderCommand.h"

#include "Platform/DirectX/DirectXRendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace UGame
{
	//todo add create method to choose between api;
#if UG_PLATFORM_WINDOWS
	RendererAPI* RenderCommand::rendererAPI = new DirectXRendererAPI;
#elif UG_PLATFORM_LINUX
	RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI;
#endif
}