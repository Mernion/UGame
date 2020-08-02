#include "WindowsWindow.h"

#include <windowsx.h>

#include "UGame/Events/ApplicationEvent.h"
#include "UGame/Events/KeyEvent.h"
#include "UGame/Events/MouseEvent.h"
#include "UGame/Log.h"
#include "UGame/Core.h"

namespace UGame
{
	static WindowData* GetAppState(HWND hwnd)
	{
		const LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
		const auto props = reinterpret_cast<WindowData*>(ptr);
		return props;
	}
	
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		const WindowData* data;
		if (uMsg == WM_CREATE)
		{
			CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
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
				break;
			}
		case WM_KEYDOWN:
			{
				KeyPressedEvent event(wParam, 0);
				data->eventCallback(event);
				break;
			}
		case WM_KEYUP:
			{
				KeyReleasedEvent event(wParam);
				data->eventCallback(event);
				break;
			}
		case WM_MOUSEMOVE:
			{
				const int xPos = GET_X_LPARAM(lParam);
				const int yPos = GET_Y_LPARAM(lParam);
				MouseMovedEvent event(xPos, yPos);
				data->eventCallback(event);
				break;
			}
		case WM_LBUTTONDOWN:
			{
				MouseButtonPressedEvent event(0);
				data->eventCallback(event);
				break;
			}
		case WM_LBUTTONUP:
			{
				MouseButtonReleasedEvent event(0);
				data->eventCallback(event);
				break;
			}
		case WM_RBUTTONDOWN:
			{
				MouseButtonPressedEvent event(1);
				data->eventCallback(event);
				break;
			}
		case WM_RBUTTONUP:
			{	
				MouseButtonReleasedEvent event(1);
				data->eventCallback(event);
				break;
			}
		case WM_MOUSEHWHEEL:
			{
				const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
				MouseScrolledEvent event(delta, 0);
				break;
			}
		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
		case WM_SIZE:
		{
			UINT width = LOWORD(lParam);
			UINT height = HIWORD(lParam);
			WindowResizeEvent event(width, height);
			data->eventCallback(event);
			break;
		}
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
	}

	void WindowsWindow::Shutdown()
	{
		//HMENU hMenu;
		//hMenu = GetMenu(hWnd);
		//if (hMenu != NULL)
		//{
		//	DestroyMenu(hMenu);
		//}
		//DestroyWindow(hWnd);
		//UnregisterClass(
		//	m_windowClassName.c_str(),
		//	m_hInstance
		//);
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