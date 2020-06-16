#pragma once
#include "Core.h"
namespace UGame
{
	class UGAME_API Application
	{

	public:

		Application();

		virtual ~Application();

		void Run();
	};

	// should be defined in the client
	Application* CreateApplication();
}


