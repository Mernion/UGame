#include "WindowsWindow.h"
#include "UGame/Events/ApplicationEvent.h"
#include "UGame/Events/KeyEvent.h"
#include "UGame/Events/MouseEvent.h"
#include "UGame/Log.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include "GLFW/glfw3.h"

namespace UGame
{
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);


			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			EndPaint(hwnd, &ps);
		}
		return 0;

		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
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

		UG_CORE_INFO("Creating window {0} ({1}, {2])", props.title, props.width, props.height);

		if (hInstance == NULL)
			hInstance = (HINSTANCE)GetModuleHandle(NULL);

		// Register the windows class
		WNDCLASSA wc{};
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = hInstance;
		wc.lpszClassName = props.title.c_str();

		RegisterClassA(&wc);

		HWND hwnd = CreateWindowExA(
			0,                              // Optional window styles.
			props.title.c_str(),					// Window class
			"Main",                        // Window text
			WS_OVERLAPPEDWINDOW,            // Window style

			// Size and position
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

			NULL,       // Parent window    
			NULL,       // Menu
			hInstance,  // Instance handle
			NULL        // Additional application data
		);

		ShowWindow(hwnd, 10);

		SetVSync(true);

		//glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		//	{
		//		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		//		data.props.height = height;
		//		data.props.width = width;

		//		WindowResizeEvent event(width, height);
		//		data.eventCallback(event);
		//	});

		//glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
		//	{
		//		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		//		WindowCloseEvent event;
		//		data.eventCallback(event);
		//	});

		//glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		//	{
		//		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		//		switch (action)
		//		{
		//		case GLFW_PRESS:
		//		{
		//			KeyPressedEvent event(key, 0);
		//			data.eventCallback(event);
		//			break;
		//		}
		//		case GLFW_RELEASE:
		//		{
		//			KeyReleasedEvent event(key);
		//			data.eventCallback(event);
		//			break;
		//		}
		//		case GLFW_REPEAT:
		//		{
		//			KeyPressedEvent event(key, 1);
		//			data.eventCallback(event);
		//			break;
		//		}
		//		}
		//	});

		//glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int character)
		//	{
		//		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		//	
		//		KeyTypedEvent event(character);
		//		data.eventCallback(event);
		//	});

		//glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		//	{
		//		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		//		switch (action)
		//		{
		//		case GLFW_PRESS:
		//		{
		//			MouseButtonPressedEvent event(button);
		//			data.eventCallback(event);
		//			break;
		//		}
		//		case GLFW_RELEASE:
		//		{
		//			MouseButtonReleasedEvent event(button);
		//			data.eventCallback(event);
		//			break;
		//		}
		//		}
		//	});

		//glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
		//	{
		//		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		//		MouseScrolledEvent event((float)xOffset, (float)yOffset);
		//		data.eventCallback(event);
		//	});

		//glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
		//	{
		//		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		//		MouseMovedEvent event((float)xPos, (float)yPos);
		//		data.eventCallback(event);
		//	});
	}

	void WindowsWindow::Shutdown()
	{
		
	}

	void WindowsWindow::OnUpdate()
	{
		MSG msg = { };
		if (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return data.VSync;
	}
}