#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace UGame
{
	class UGAME_API Application
	{

	public:

		Application();

		virtual ~Application();

		void Run();
	private:

		std::unique_ptr<Window> window;
		bool running = true;
	};

	// should be defined in the client
	Application* CreateApplication();
}


