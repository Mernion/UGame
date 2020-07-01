#include "UGame.h"

class ExampleLayer : public UGame::Layer
{
public:

	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		if (UGame::Input::IsKeyPressed(UG_KEY_TAB))
		{
			UG_TRACE("tab key is pressed");
		}
	}

	void OnEvent(UGame::Event& event) override
	{
	}
};

class Sandbox : public UGame::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new UGame::ImGuiLayer());
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