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
		const float vertices[] = {
			-0.5f, -0.5f, 0.f,
			0.f, 0.5f, 0.f,
			0.5f, -0.5f, 0.f
		};

		unsigned int vertexArray;
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		unsigned int vertexBuffer;
		glCreateBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		const std::string vertexShaderSrc = R"(
			#version 330 core
			layout (location = 0) in vec3 aPos;

			void main()
			{
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
			})";
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* vertexSrc = vertexShaderSrc.c_str();
		glShaderSource(vertexShader, 1, &vertexSrc, NULL);
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);
			return;
		}

		const std::string fragmentShaderSrc = R"(
		#version 330 core
		out vec4 FragColor;
		
		void main()
		{
			FragColor = vec4(1.f, 0.5f, 0.2f, 1.f);
		})";

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		const GLchar* fragmentSrc = vertexShaderSrc.c_str();
		glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);
		glCompileShader(fragmentShader);

		GLint isFragmentCompiled = 0;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isFragmentCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			return;
		}

		unsigned int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glUseProgram(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);



		while (running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			glDrawArrays(GL_TRIANGLES, 0, 3);


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