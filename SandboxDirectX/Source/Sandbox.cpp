#include <d3d11.h>
#include <d3d11shader.h>
#include <dxgi.h>

#include "UGame.h"



class ExampleLayer : public UGame::Layer
{
public:

	ExampleLayer() : Layer("Example")
	{
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 2;
		sd.BufferDesc.Width = 640;
		sd.BufferDesc.Height = 480;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = (HWND)UGame::Application::Get().GetWindow().GetNativeWindow();
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		UINT createDeviceFlags = 0;
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
		HRESULT result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &swapChain, &device, &deviceFeatureLevel, &deviceContext);
		if (result != S_OK)
			DWORD error = GetLastError();

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

	IDXGISwapChain* swapChain;
	ID3D11Device* device;
	D3D_FEATURE_LEVEL deviceFeatureLevel;
	ID3D11DeviceContext* deviceContext;

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