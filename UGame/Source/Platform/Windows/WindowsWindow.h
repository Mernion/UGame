#pragma once
#include "UGame/Window.h"
#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace UGame
{
	class WindowsWindow : public Window
	{
	public:
		
		WindowsWindow(const WindowProps& Window);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		int GetWidth() const override { return data.props.width; }
		int GetHeight() const override { return data.props.height; }

		void SetEventCallback(const EventCallbackFn& callback) override
		{
			data.eventCallback = callback;
		}

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		
		void* GetNativeWindow() const override { return hInstance; }

	private:

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		HINSTANCE hInstance;
		GraphicsContext* graphicsContext;

		struct WindowData
		{
			WindowProps props;
			bool VSync;

			EventCallbackFn eventCallback;
		} data;

	};
}


