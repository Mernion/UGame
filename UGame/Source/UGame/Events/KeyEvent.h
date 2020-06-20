#pragma once

#include "Event.h"


namespace UGame
{
	// treat as abstract class; should not be created directly
	class UGAME_API KeyEvent : public Event
	{
	public:

		EVENT_CLASS_TYPE(KeyEvent)
		
		int GetCategoryFlags() const override { return static_cast<int>(EventCategory::Keyboard) | static_cast<int>(EventCategory::Input); }

		inline int GetKeyCode() const { return keyCode; }

	protected:

		KeyEvent(int keyCode) : keyCode(keyCode) {}

		int keyCode;
	};

	class UGAME_API KeyPressedEvent : public KeyEvent
	{
		EVENT_CLASS_TYPE(KeyPressedEvent)

		KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), repeatCount(repeatCount)
		{}

		inline int GetRepeatCount() const { return repeatCount; }
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << keyCode << " (" << repeatCount << " repeats)";
			return ss.str();
		}

	private:

		int repeatCount;
	};

	class UGAME_API KeyReleasedEvent : public KeyEvent
	{
	public:

		EVENT_CLASS_TYPE(KeyReleased)

		KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << keyCode;
			return ss.str();
		}
	};
}