#include "ugpch.h"
#include "WindowsWindow.h"

namespace UGame
{
	static bool GLFWInitialized{ false };

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		data.props = props;

		//UG_CORE_INFO("Creating window {0} ({1}, {2])", props.title, props.width, props.height);

		if (!GLFWInitialized)
		{
			int success = glfwInit();
			//UG_CORE_ASSERT(success, "Could not intiialize GLFW");
			
			GLFWInitialized = true;
		}

		window = glfwCreateWindow(props.width,
			props.height,
			props.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &data);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		enabled ? glfwSwapInterval(1) : glfwSwapInterval(0);
		data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return data.VSync;
	}
}