#pragma once
#include "UGame/ImGui/ImGuiLayer.h"

namespace UGame
{
	class UGAME_API DirectXImGuiLayer : public ImGuiLayer
	{
	public:
		
		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender(ImGuiContext *const context) override;

		void Begin();
		void End();

	private:

		float deltaTime = 0.f;
		
		bool CreateDeviceD3D(HWND hwnd);
		void CleanupDeviceD3D();
		void CreateRenderTarget();
		void CleanupRenderTarget();
		
	};
}