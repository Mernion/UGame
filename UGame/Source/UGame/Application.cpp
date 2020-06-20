#include "ugpch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace UGame
{
	Application::Application()
	{
		;
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(640, 480);
		UG_TRACE(e);

		while (true)
		{

		}
	}
}