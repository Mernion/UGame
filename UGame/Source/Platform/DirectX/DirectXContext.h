#pragma once
#include "Renderer/GraphicsContext.h"
#include <d3d11.h>
#include <d3d11shader.h>
#include <dxgi.h>

namespace UGame
{
	class DirectXContext : public GraphicsContext
	{
	public:

		DirectXContext(HWND hwnd);

		void Init() override;
		void SwapBuffers() override;

		ID3D11Device* GetDevice() const { return device; }
		ID3D11DeviceContext* GetDeviceContext() const { return deviceContext; }

	private:

		IDXGISwapChain* swapChain;
		ID3D11Device* device;
		D3D_FEATURE_LEVEL deviceFeatureLevel;
		ID3D11DeviceContext* deviceContext;

		HWND hwnd;
	};
}