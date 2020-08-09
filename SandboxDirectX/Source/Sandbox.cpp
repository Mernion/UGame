#include <d3d11.h>
#include <d3d11shader.h>
#include <dxgi.h>

#include "UGame.h"



class ExampleLayer : public UGame::Layer
{
public:

	ExampleLayer() : Layer("Example")
	{


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