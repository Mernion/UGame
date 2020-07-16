#pragma once

namespace UGame
{
	enum class RendererAPI
	{
		None,
		OpenGL
	};
	
	class Renderer
	{
	public:
		static RendererAPI GetAPI() { return API; };

	private:
		static RendererAPI API;
	};
}