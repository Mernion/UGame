#include "WindowsWindow.h"


#include <imgui.h>

#include <windowsx.h>

#include "UGame/Events/ApplicationEvent.h"
#include "UGame/Events/KeyEvent.h"
#include "UGame/Events/MouseEvent.h"
#include "UGame/Log.h"
#include "UGame/Core.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


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
		if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
			return true;
		
		const WindowData* data;
		if (uMsg == WM_CREATE)
		{
			CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
			data = reinterpret_cast<WindowData*>(pCreate->lpCreateParams);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)data);
			return 0;
		}

		data = GetAppState(hwnd);
		
		switch (uMsg)
		{
		case WM_CLOSE:
			{
				WindowCloseEvent event;
				data->eventCallback(event);
				return 0;
			}
		case WM_KEYDOWN:
			{
				KeyPressedEvent event(wParam, 0);
				data->eventCallback(event);
				return 0;
			}
		case WM_KEYUP:
			{
				KeyReleasedEvent event(wParam);
				data->eventCallback(event);
				return 0;
			}
		case WM_MOUSEMOVE:
			{
				const int xPos = GET_X_LPARAM(lParam);
				const int yPos = GET_Y_LPARAM(lParam);
				MouseMovedEvent event(xPos, yPos);
				data->eventCallback(event);
				return 0;
			}
		case WM_LBUTTONDOWN:
			{
				MouseButtonPressedEvent event(0);
				data->eventCallback(event);
				return 0;
			}
		case WM_LBUTTONUP:
			{
				MouseButtonReleasedEvent event(0);
				data->eventCallback(event);
				return 0;
			}
		case WM_RBUTTONDOWN:
			{
				MouseButtonPressedEvent event(1);
				data->eventCallback(event);
				return 0;
			}
		case WM_RBUTTONUP:
			{	
				MouseButtonReleasedEvent event(1);
				data->eventCallback(event);
				return 0;
			}
		case WM_MOUSEHWHEEL:
			{
				const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
				MouseScrolledEvent event(delta, 0);
				return 0;
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
			return 0;
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
		;
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		windowData.props = props;

		UG_CORE_INFO("Creating window {0} ({1}, {2])", props.title, props.width, props.height);

		// Register the windows class
		const std::wstring wTitle = std::wstring(props.title.begin(), props.title.end());
		WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WindowProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, wTitle.c_str(), NULL };
		
		RegisterClassEx(&wc);
		hwnd = ::CreateWindow(wc.lpszClassName, L"Main", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, &windowData);

		ShowWindow(hwnd, SW_SHOWDEFAULT);

		SetVSync(true);

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