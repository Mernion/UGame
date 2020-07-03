#include "Application.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Layer.h"
#include "Input.h"
#include "Log.h"

#include "glad/glad.h"

namespace UGame
{
	Application* Application::instance = nullptr;

	Application::Application()
	{
		UG_CORE_ASSERT(!instance, "Application already exist");
		instance = this;

		window = std::unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_EVENT(Application::OnEvent));

		imGuiLayer = new ImGuiLayer();
		layerStack.PushOverlay(imGuiLayer);
	}

	Application::~Application()
	{
		
	}

	void Application::PushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		layerStack.PushOverlay(overlay);
	}

	void Application::Run()
	{
		while (running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			for (Layer* layer : layerStack)
			{
				layer->OnUpdate();
			}

			imGuiLayer->Begin();
			for (Layer* layer : layerStack)
			{
				layer->OnImGuiRender();
			}
			imGuiLayer->End();

			window->OnUpdate();
		}
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(Application::OnWindowClose));

		for (auto it = layerStack.end();it != layerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.getHandled())
			{
				break;
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		running = false;

		return true;
	}
}