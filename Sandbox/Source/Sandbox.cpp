#include "UGame.h"

#include "imgui.h"

class ExampleLayer : public UGame::Layer
{
public:

	ExampleLayer() : Layer("Example") 
	{
	}

	void OnUpdate() override
	{
		if (UGame::Input::IsKeyPressed(UG_KEY_TAB))
		{
			UG_TRACE("tab key is pressed");
		}
	}

	void OnImGuiRender() override
	{
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