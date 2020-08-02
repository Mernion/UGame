#include "UGame.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public UGame::Layer
{
public:

	ExampleLayer() : Layer("Example"), camera(1.666, true)
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

		shader = UGame::Shader::Create("shaders/Color.glsl");
		auto textureShader = shaderLibrary.Load("shaders/Texture.glsl");
		
		texture = UGame::Texture2D::Create("textures/Checkerboard.png");
		logoTexture = UGame::Texture2D::Create("textures/ChernoLogo.png");
		
		textureShader->Bind();
		textureShader->UploadUniformInt("u_Texture", 0);
	
		float squareVertices[5 * 4] = {
			-0.5f,	-0.5f,	0.0f, 0.f, 0.f,
			 0.5f,	-0.5f,	0.0f, 1.f, 0.f,
			 0.5f,	 0.5f,	0.0f, 1.f, 1.f,
			-0.5f,	 0.5f,	0.f,  0.f, 1.f
		};
		squareVB.reset(UGame::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ UGame::ShaderDataType::Float3, "a_Position"},
			{ UGame::ShaderDataType::Float2, "a_TexCoord"}
		});
		squareVA.reset(UGame::VertexArray::Create());
		squareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		squareIB.reset(UGame::IndexBuffer::Create(squareIndices, sizeof(squareIndices)));
		squareVA->SetIndexBuffer(squareIB);
	}

	void OnUpdate(UGame::Timestep timestep) override
	{
		camera.OnUpdate(timestep);
		
		UGame::RenderCommand::SetClearColor({ 0.2, 0.2, 0.2, 0.2 });
		UGame::RenderCommand::Clear();

		UGame::Renderer::BeginScene(camera.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(0.1f));
		for (int y=0; y < 20; y++)
		{
			for (int x=0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.f);
				glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * scale;
				shader->UploadUniformFloat4("u_Color", color);
				UGame::Renderer::Submit(vertexArray, shader, transform);
			}
		}

		texture->Bind();
		UGame::Renderer::Submit(squareVA, shaderLibrary.Get("Texture"));
		//logoTexture->Bind();
		//UGame::Renderer::Submit(squareVA, textureShader);

		
		UGame::Renderer::EndScene();
	}

	//todo:: set context at OnAttach instead of render? this because of dll, globals are not shared across dll :(
	void OnImGuiRender(ImGuiContext* const context) override
	{
		ImGui::SetCurrentContext(context);
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(color));
		ImGui::End();	
	}

	void OnEvent(UGame::Event& event) override
	{
		camera.OnEvent(event);
	}

private:
	UGame::ShaderLibrary shaderLibrary;
	
	std::shared_ptr<UGame::Shader> shader;
	
	std::shared_ptr<UGame::VertexArray> vertexArray;
	std::shared_ptr<UGame::VertexBuffer> vertexBuffer;
	std::shared_ptr<UGame::IndexBuffer> indexBuffer;

	std::shared_ptr<UGame::VertexArray> squareVA;
	std::shared_ptr<UGame::VertexBuffer> squareVB;
	std::shared_ptr<UGame::IndexBuffer> squareIB;

	std::shared_ptr<UGame::Texture2D> texture, logoTexture;
	
	UGame::OrthographicCameraController camera;
	glm::vec4 color{ 0.f };
};

class Sandbox : public UGame::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
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