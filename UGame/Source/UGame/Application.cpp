#include "Application.h"

#include <imgui.h>
#include <imgui_internal.h>

#include "Core/Timestep.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "GLFW/glfw3.h"
#include "Layer.h"
#include "Input.h"
#include "Log.h"
#include "Renderer/Renderer.h"

namespace UGame
{
	Application* Application::instance = nullptr;

	Application::Application()
	{
		UG_CORE_ASSERT(!instance, "Application already exist");
		instance = this;

		window = std::unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_EVENT(Application::OnEvent));

		Renderer::Init();
		
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
			const float time = static_cast<float>(glfwGetTime()); // todo:: add platform independent solution
			Timestep timestep = time - lastFrameTime;
			lastFrameTime = time;
			
			for (Layer* layer : layerStack)
			{
				layer->OnUpdate(timestep);
			}

			imGuiLayer->Begin();
			for (Layer* layer : layerStack)
			{
				layer->OnImGuiRender(ImGui::GetCurrentContext());
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
