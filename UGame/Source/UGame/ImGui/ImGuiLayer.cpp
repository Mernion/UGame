#include "ImGuiLayer.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "UGame/Application.h"
#include "UGame/Events/Event.h"
#include "UGame/Events/MouseEvent.h"
#include "UGame/Events/ApplicationEvent.h"
#include "UGame/Events/KeyEvent.h"

#include "GLFW/glfw3.h" //tmp
#include "glad/glad.h"


namespace UGame
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{
		;
	}


	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0;
			style.Colors[ImGuiCol_WindowBg].w = 1.f;
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

	}
		
	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}
}