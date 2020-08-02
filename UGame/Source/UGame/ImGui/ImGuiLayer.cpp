#include "ImGuiLayer.h"
#include "DirectX/DirectXImGuiLayer.h"
#include "OpenGL/OpenGLImGuiLayer.h"

namespace UGame
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
	{

	}

	ImGuiLayer* ImGuiLayer::Create()
	{
#ifdef UG_PLATFORM_WINDOWS
		return new DirectXImGuiLayer();
#elif UG_PLATFORM_LINUX
		return new OpenGLImGuiLayer();
#endif
		UG_CORE_ASSERT("Not support plaftom for imgui");
		return nullptr;
	}

	
}