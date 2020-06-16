#include "UGame.h"

class Sandbox : public UGame::Application
{
public:
	Sandbox()
	{
		;
	}

	~Sandbox()
	{
		;
	}
};

UGame::Application* UGame::CreateApplication()
{
	return new Sandbox();
}