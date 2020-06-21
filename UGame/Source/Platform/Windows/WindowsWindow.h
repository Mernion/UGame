#pragma once
#include "UGame/Window.h"
#include "GLFW/glfw3.h"

namespace UGame
{
	class WindowsWindow : public Window
	{
	public:
		
		WindowsWindow(const WindowProps& Window);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline int GetWidth() const override { return data.props.width; }
		inline int GetHeight() const override { return data.props.height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override
		{
			data.eventCallback = callback;
		}

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		GLFWwindow* window;

		struct WindowData
		{
			WindowProps props;
			bool VSync;

			EventCallbackFn eventCallback;
		} data;

	};
}

