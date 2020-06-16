#pragma once

#ifdef UG_PLATFORM_WINDOWS

extern UGame::Application* UGame::CreateApplication();

int main(int argc, char** argv)
{
	UGame::Log::Init();
	UG_CORE_WARN("Initialized log");

	auto app = UGame::CreateApplication();
	app->Run();
	delete app;
}

#endif