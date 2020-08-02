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
#include "Platform/Windows/WindowsWindow.h"
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
		WindowsWindow* ww = (WindowsWindow*)window.get();
		ww->Init({});
		
		//Renderer::Init();
		
		imGuiLayer = ImGuiLayer::Create();
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
			window->OnUpdate();
			
			//const float time = static_cast<float>(glfwGetTime()); // todo:: add platform independent solution
			//Timestep timestep = time - lastFrameTime;
			//lastFrameTime = time;

			//if (!minimized)
			//{
			//	for (Layer* layer : layerStack)
			//	{
			//		layer->OnUpdate(timestep);
			//	}
			//}

			imGuiLayer->Begin();
			for (Layer* layer : layerStack)
			{
				layer->OnImGuiRender(ImGui::GetCurrentContext());
			}
			imGuiLayer->End();

			//window->OnUpdate();
		}
	}
	
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT(Application::OnWindowResize));
		
		for (auto it = layerStack.end();it != layerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.getHandled())
			{
				break;
			}
		}
	}
	
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			minimized = true;
			return false;
		}

		minimized = false;
		//Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		running = false;

		return true;
	}
}
