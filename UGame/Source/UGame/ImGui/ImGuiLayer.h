#pragma once
#include "UGame/Layer.h"

class MouseMovedEvent;
class MouseScrolledEvent;
class MouseButtonEvent;
class WindowResizeEvent;
class KeyReleasedEvent;
class KeyPressedEvent;
class KeyTypedEvent;

namespace UGame
{
	class UGAME_API ImGuiLayer : public Layer
	{
	public:
		
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();

	private:

		float deltaTime = 0.f;
	};
}