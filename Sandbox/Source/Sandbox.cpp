#include "UGame.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public UGame::Layer
{
public:

	ExampleLayer() : Layer("Example"), camera(-1.f, 1.f, -1.f, 1.f)
	{
		float vertices[] = {
			-0.5f, -0.5f, 0.f,
			0.f, 0.5f, 0.f,
			0.5f, -0.5f, 0.f
		};
		vertexBuffer.reset(UGame::VertexBuffer::Create(vertices, sizeof(vertices)));
		UGame::BufferLayout layout =
		{
			{UGame::ShaderDataType::Float3, "a_Position"}
		};
		vertexBuffer->SetLayout(layout);

		unsigned int indecies[] = {
			0, 1, 2
		};
		indexBuffer.reset(UGame::IndexBuffer::Create(indecies, sizeof(indecies)));

		vertexArray.reset(UGame::VertexArray::Create());
		vertexArray->AddVertexBuffer(vertexBuffer);
		vertexArray->SetIndexBuffer(indexBuffer);

		const std::string vertexShaderSrc = R"(
			#version 410 core
		
			layout (location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

		
			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		const std::string fragmentShaderSrc = R"(
			#version 410 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		shader.reset(UGame::Shader::Create(vertexShaderSrc, fragmentShaderSrc));
	}

	void OnUpdate(UGame::Timestep timestep) override
	{
		if (UGame::Input::IsKeyPressed(UG_KEY_LEFT))
		{
			cameraPosition.x += cameraMoveSpeed * timestep;
		}
		else if (UGame::Input::IsKeyPressed(UG_KEY_RIGHT))
		{
			cameraPosition.x -= cameraMoveSpeed * timestep;
		}

		if (UGame::Input::IsKeyPressed(UG_KEY_UP))
		{
			cameraPosition.y -= cameraMoveSpeed * timestep;
		}
		else if (UGame::Input::IsKeyPressed(UG_KEY_DOWN))
		{
			cameraPosition.y += cameraMoveSpeed * timestep;
		}

		if (UGame::Input::IsKeyPressed(UG_KEY_A))
		{
			cameraRotation -= cameraRotationSpeed * timestep;
		}

		if (UGame::Input::IsKeyPressed(UG_KEY_D))
		{
			cameraRotation += cameraRotationSpeed * timestep;
		}
		
		UGame::RenderCommand::SetClearColor({ 0.2, 0.2, 0.2, 0.2 });
		UGame::RenderCommand::Clear();

		camera.SetPosition(cameraPosition);
		camera.SetRotation(cameraRotation);
		
		UGame::Renderer::BeginScene(camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(0.1f));
		for (int y=0; y < 20; y++)
		{
			for (int x=0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.f);
				glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * scale;
				UGame::Renderer::Submit(vertexArray, shader, transform);
			}
		}

		//UGame::Renderer::Submit(vertexArray, shader);

		UGame::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		
	}

	void OnEvent(UGame::Event& event) override
	{
		UGame::EventDispatcher dispatcher(event);
		//dispatcher.Dispatch<UGame::KeyPressedEvent>(BIND_EVENT(ExampleLayer::OnKeyPressedEvent));
	}

private:
	std::shared_ptr<UGame::Shader> shader;
	std::shared_ptr<UGame::VertexArray> vertexArray;
	std::shared_ptr<UGame::VertexBuffer> vertexBuffer;
	std::shared_ptr<UGame::IndexBuffer> indexBuffer;

	UGame::OrthographicCamera camera;
	glm::vec3 cameraPosition{0.f};
	float cameraRotation{ 0.f };
	float cameraMoveSpeed{ 0.1f };
	float cameraRotationSpeed{ 2.f };
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