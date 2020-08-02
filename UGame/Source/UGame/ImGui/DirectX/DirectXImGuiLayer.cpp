#include "DirectXImGuiLayer.h"

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include "UGame/Application.h"

namespace UGame
{

	void DirectXImGuiLayer::OnAttach()
	{

	}

	void DirectXImGuiLayer::OnDetach()
	{

	}

	void DirectXImGuiLayer::Begin()
	{

	}

	void DirectXImGuiLayer::End()
	{

	}
		
	void DirectXImGuiLayer::OnImGuiRender(ImGuiContext* const context)
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}
}