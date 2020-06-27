#include "UGame.h"

class ExampleLayer : public UGame::Layer
{
public:

	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		UG_INFO("{0}", __func__);
	}

	void OnEvent(UGame::Event& event) override
	{
		UG_TRACE("{0}", event);
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