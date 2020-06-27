#pragma once
#include "UGame/Layer.h"

namespace UGame
{
	class UGAME_API ImGuiLayer : public Layer
	{
	public:
		
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;

	private:

		float deltaTime;
	};
}