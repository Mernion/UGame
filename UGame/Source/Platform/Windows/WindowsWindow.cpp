#include "WindowsWindow.h"
#include "UGame/Events/ApplicationEvent.h"
#include "UGame/Events/KeyEvent.h"
#include "UGame/Events/MouseEvent.h"
#include "UGame/Log.h"

namespace UGame
{
	static WindowData* GetAppState(HWND hwnd)
	{
		LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
		WindowData* props = reinterpret_cast<WindowData*>(ptr);
		return props;
	}
	
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		const WindowData* data;
		if (uMsg == WM_CREATE)
		{
			CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
			data = reinterpret_cast<WindowData*>(pCreate->lpCreateParams);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)data);
		}
		else
		{
			data = GetAppState(hwnd);
		}
		
		switch (uMsg)
		{
		case WM_CLOSE:
			{
				WindowCloseEvent event;
				data->eventCallback(event);
			}
		case WM_KEYDOWN:
			{
				KeyPressedEvent event(wParam, 0);
				data->eventCallback(event);
			}
		case WM_KEYUP:
			{
				KeyReleasedEvent event(wParam);
				data->eventCallback(event);
			}
			
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

		UG_CORE_INFO("Window event {0}", uMsg);
		
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
		windowData.props = props;

		UG_CORE_INFO("Creating window {0} ({1}, {2])", props.title, props.width, props.height);

		if (hInstance == NULL)
			hInstance = static_cast<HINSTANCE>(GetModuleHandle(NULL));

		// Register the windows class
		WNDCLASS wc{};
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = hInstance;
		std::wstring wTitle = std::wstring(props.title.begin(), props.title.end());
		wc.lpszClassName = wTitle.c_str();

		RegisterClass(&wc);

		HWND hwnd = CreateWindowEx(
			0,											// Optional window styles.
		wTitle.c_str(),							// Window class
		L"Main",								// Window text
			WS_OVERLAPPEDWINDOW,					// Window style

			// Size and position
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,									// Parent window    
			NULL,									// Menu
			hInstance,									// Instance handle
			&windowData									// Additional application data
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

		//glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		//	{
		//		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

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
		MSG msg{};
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		windowData.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return windowData.VSync;
	}
}