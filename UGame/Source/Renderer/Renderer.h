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
		inline static RendererAPI GetAPI();

	private:
		static RendererAPI API;
	};
}