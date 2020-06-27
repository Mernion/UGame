#pragma once
#include "Core.h"
#include "LayerStack.h"

#include "Window.h"

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

	private:

		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> window;
		bool running = true;

		LayerStack layerStack;
	};

	// should be defined in the client
	Application* CreateApplication();
}


