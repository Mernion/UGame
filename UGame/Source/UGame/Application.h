#pragma once
#include "Core.h"
#include "LayerStack.h"
#include <memory>

#include "Window.h"
#include "UGame/ImGui/ImGuiLayer.h"

namespace UGame
{
	class Layer;
	class Event;
	class WindowCloseEvent;
	class WindowResizeEvent;

	class UGAME_API Application
	{

	public:
		Application();

		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *window; }

		static Application& Get() { return *instance; }

	private:

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> window;
		ImGuiLayer* imGuiLayer;
		bool running = true;
		bool minimized = false;

		LayerStack layerStack;

		static Application* instance;

		float lastFrameTime{ 0.f };
	};

	// should be defined in the client
	Application* CreateApplication();
}


