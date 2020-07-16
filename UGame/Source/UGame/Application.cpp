#include "Application.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Layer.h"
#include "Input.h"
#include "Log.h"

#include "Renderer/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"

#include "Renderer/BufferLayout.h"

#include "glad/glad.h"
#include <memory>


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

		float vertices[] = {
			-0.5f, -0.5f, 0.f,
			0.f, 0.5f, 0.f,
			0.5f, -0.5f, 0.f
		};
		std::shared_ptr<VertexBuffer> vertexBuffer{ VertexBuffer::Create(vertices, sizeof(vertices)) };
		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "a_Position"}
		};
		vertexBuffer->SetLayout(layout);

		unsigned int indecies[] = {
			0, 1, 2
		};
		std::shared_ptr<IndexBuffer> indexBuffer{ IndexBuffer::Create(indecies, sizeof(indecies)) };

		std::unique_ptr<VertexArray> vertexArray{ VertexArray::Create() };
		vertexArray->AddVertexBuffer(vertexBuffer);
		vertexArray->SetIndexBuffer(indexBuffer);
		
		const std::string vertexShaderSrc = R"(
			#version 410 core
		
			layout (location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			})";

		const std::string fragmentShaderSrc = R"(
		#version 410 core

		layout(location = 0) out vec4 color;

		in vec3 v_Position;
		
		void main()
		{
			color = vec4(v_Position * 0.5 + 0.5, 1.0);
		})";

		std::unique_ptr<Shader> shader = std::make_unique<OpenGLShader>(vertexShaderSrc, fragmentShaderSrc);

		while (running)
		{
			glClearColor(0.2, 0.2, 0.2, 0.2);
			glClear(GL_COLOR_BUFFER_BIT);

			shader->Bind();
			vertexArray->Bind();
			glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
			
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

		shader->Unbind();
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