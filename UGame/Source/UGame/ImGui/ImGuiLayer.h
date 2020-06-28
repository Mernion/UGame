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
		void OnUpdate() override;
		void OnEvent(Event& event) override;

	private:

		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseButtonPressedEvent(MouseButtonEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonEvent& event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& event);
		bool OnWindowResizedEvent(WindowResizeEvent& event);
		bool OnKeyTypedEvent(KeyTypedEvent& event);

		float deltaTime = 0.f;
	};
}