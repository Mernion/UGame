#pragma once
#include "UGame/ImGui/ImGuiLayer.h"


namespace UGame
{
	class UGAME_API OpenGLImGuiLayer : public ImGuiLayer
	{
	public:
		
		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender(ImGuiContext *const context) override;

		void Begin() override;
		void End() override;

	private:

		float deltaTime = 0.f;
	};
}