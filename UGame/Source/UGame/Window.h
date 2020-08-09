#pragma once
#include "Core.h"
#include "Events/Event.h"

namespace UGame
{
	class GraphicsContext;
	
	struct WindowProps
	{
		std::string title;
		int width;
		int height;

		WindowProps(const std::string& title = "UGame Engine",
			int width = 1280,
			int height = 720) : title(title), width(width), height(height)
		{
		}
	};

	class UGAME_API Window
	{
	public:
		
		using EventCallbackFn = std::function<void(Event&)>;
		
		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		
		virtual void* GetNativeWindow() const = 0;
		virtual GraphicsContext* GetGraphicsContext() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};


}