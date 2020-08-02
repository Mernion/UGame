#pragma once
#include "UGame/Window.h"
#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace UGame
{
	class LinuxWindow : public Window
	{
	public:
		
		LinuxWindow(const WindowProps& Window);
		virtual ~LinuxWindow();

		void OnUpdate() override;

		int GetWidth() const override { return data.props.width; }
		int GetHeight() const override { return data.props.height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override
		{
			data.eventCallback = callback;
		}

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		
		void* GetNativeWindow() const override { return window; }

	private:

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		GLFWwindow* window;
		GraphicsContext* graphicsContext;

		struct WindowData
		{
			WindowProps props;
			bool VSync;

			EventCallbackFn eventCallback;
		} data;

	};
}


