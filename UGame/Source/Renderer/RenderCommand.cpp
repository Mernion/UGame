#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace UGame
{
	//todo add create method to choose between api;
	RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI;
}