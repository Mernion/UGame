#pragma once

#include "Event.h"
#include <sstream>
#include "UGame/Core.h"

namespace UGame
{
	class UGAME_API MouseMovedEvent : public Event
	{
	public:

		EVENT_CLASS_TYPE(MouseMoved);

		MouseMovedEvent(float mouseX, float mouseY) : mouseX(mouseX), mouseY(mouseY) {}

		inline float GetX() const { return mouseX; }
		inline float GetY() const { return mouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << mouseX << " , " << mouseY;
			return ss.str();
		}

		int GetCategoryFlags() const override
		{
			return static_cast<int>(EventCategory::Mouse) | static_cast<int>(EventCategory::Input);
		}

	private:

		float mouseX, mouseY;
	};

	class UGAME_API MouseScrolledEvent : public MouseMovedEvent
	{
	public:

		EVENT_CLASS_TYPE(MouseScrolled)

		MouseScrolledEvent(float X, float Y) : MouseMovedEvent(X, Y) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetX() << " , " << GetY();
			return ss.str();
		}

		int GetCategoryFlags() const override
		{
			return static_cast<int>(EventCategory::Mouse) | static_cast<int>(EventCategory::Input);
		}
	};

	class UGAME_API MouseButtonEvent : public Event
	{
	public:

		inline int GetMouseButton() const { return button; }

		int GetCategoryFlags() const override
		{
			return static_cast<int>(EventCategory::Mouse) | static_cast<int>(EventCategory::Input);
		}

	protected:

		MouseButtonEvent(int button) : button(button) {}

		int button;
	};

	class UGAME_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:

		EVENT_CLASS_TYPE(MouseButtonPressed)

		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressed: " << GetMouseButton();
			return ss.str();
		}
	};

	class UGAME_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:

		EVENT_CLASS_TYPE(MouseButtonReleased)

		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleased: " << GetMouseButton();
			return ss.str();
		}

	};
}