#include "OpenGLContext.h"

#include "UGame/Core.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace UGame
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	{
		window = windowHandle;
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		UG_CORE_ASSERT(status, "Failed to initialize Glad");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}

}