#include <d3d11.h>

#include "UGame.h"



class ExampleLayer : public UGame::Layer
{
public:

	ExampleLayer() : Layer("Example")
	{

		float vertex_data_array[] = {
   0.0f,  0.5f,  0.0f, // point at top
   0.5f, -0.5f,  0.0f, // point at bottom-right
  -0.5f, -0.5f,  0.0f, // point at bottom-left
		};
		UINT vertex_stride = 3 * sizeof(float);
		UINT vertex_offset = 0;
		UINT vertex_count = 3;

		vertexBuffer.reset(UGame::VertexBuffer::Create(vertex_data_array, sizeof(vertex_data_array)));
		
		const std::string shaderSrc = R"(
			struct vs_in {
				float3 position_local : POS;
			};

			/* outputs from vertex shader go here. can be interpolated to pixel shader */
			struct vs_out {
				float4 position_clip : SV_POSITION; // required output of VS
			};

			vs_out vs_main(vs_in input) {
				vs_out output = (vs_out)0; // zero the memory first
				output.position_clip = float4(input.position_local, 1.0);
				return output;
			}

			float4 ps_main(vs_out input) : SV_TARGET{
			  return float4(1.0, 0.0, 1.0, 1.0); // must return an RGBA colour
			}
		)";

		shader = UGame::Shader::Create("TestShader", shaderSrc, shaderSrc);

	}

	void OnUpdate(UGame::Timestep timestep) override
	{

	}

	//todo:: set context at OnAttach instead of render? this because of dll, globals are not shared across dll :(
	void OnImGuiRender(ImGuiContext* const context) override
	{

	}

	void OnEvent(UGame::Event& event) override
	{
		
	}

private:


	std::shared_ptr<UGame::VertexBuffer> vertexBuffer;
	std::shared_ptr<UGame::Shader> shader;
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