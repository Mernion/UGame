#pragma once
#include "UGame/Window.h"
#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace UGame
{
	struct WindowData
	{
		WindowProps props;
		bool VSync;

		Window::EventCallbackFn eventCallback;
	};
	
	class WindowsWindow : public Window
	{
	public:
		
		WindowsWindow(const WindowProps& Window);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		int GetWidth() const override { return windowData.props.width; }
		int GetHeight() const override { return windowData.props.height; }

		void SetEventCallback(const EventCallbackFn& callback) override
		{
			windowData.eventCallback = callback;
		}

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		
		void* GetNativeWindow() const override { return hInstance; }

	private:

		WindowData windowData;

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		HINSTANCE hInstance;
		GraphicsContext* graphicsContext;
	};
}


