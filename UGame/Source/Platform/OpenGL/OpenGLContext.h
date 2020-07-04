#pragma once
#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace UGame
{
	class OpenGLContext : public GraphicsContext
	{
	public:

		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* window;
	};
}