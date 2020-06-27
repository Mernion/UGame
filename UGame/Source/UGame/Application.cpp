#include "ugpch.h"
#include "Application.h"

#include "Log.h"

#include <GLFW/glfw3.h>

namespace UGame
{
	Application::Application()
	{
		window = std::unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_EVENT(Application::OnEvent));
	}

	Application::~Application()
	{
		
	}

	void Application::Run()
	{
		while (running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			window->OnUpdate();
		}
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(Application::OnWindowClose));

		UG_CORE_INFO("{0}", e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		running = false;

		return true;
	}
}