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

	class UGAME_API Application
	{

	public:
		Application();

		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *window; }

		inline static Application& Get() { return *instance; }

	private:

		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> window;
		ImGuiLayer* imGuiLayer;
		bool running = true;

		LayerStack layerStack;

		static Application* instance;
	};

	// should be defined in the client
	Application* CreateApplication();
}


