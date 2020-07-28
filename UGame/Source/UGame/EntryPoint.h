#pragma once


#ifdef UG_PLATFORM_LINUX

extern UGame::Application* UGame::CreateApplication();

int main(int argc, char** argv)
{
	UGame::Log::Init();
	UG_CORE_WARN("Initialized log");

	auto app = UGame::CreateApplication();
	app->Run();
	delete app;
}

#elif UG_PLATFORM_WINDOWS

extern UGame::Application* UGame::CreateApplication();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	UGame::Log::Init();
	UG_CORE_WARN("Initialized log");

	auto app = UGame::CreateApplication();
	app->Run();
	delete app;

	return 0;
}


#endif