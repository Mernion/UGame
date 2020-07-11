#include "Renderer.h"

namespace UGame
{
	RendererAPI Renderer::API = RendererAPI::OpenGL;
	
	RendererAPI Renderer::GetAPI() 
	{
		return API;
	}
}
