#pragma once

#include "Event.h"
#include <sstream>


namespace UGame
{
	// treat as abstract class; should not be created directly
	class UGAME_API KeyEvent : public Event
	{
	public:

		int GetCategoryFlags() const override { return static_cast<int>(EventCategory::Keyboard) | static_cast<int>(EventCategory::Input); }

		int GetKeyCode() const { return keyCode; }

	protected:

		KeyEvent(int keyCode) : keyCode(keyCode) {}

		int keyCode;
	};

	class UGAME_API KeyPressedEvent : public KeyEvent
	{
	public:

		EVENT_CLASS_TYPE(KeyPressed)

		KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), repeatCount(repeatCount)
		{}

		int GetRepeatCount() const { return repeatCount; }
		
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

	class UGAME_API KeyTypedEvent : public KeyEvent
	{
	public:

		EVENT_CLASS_TYPE(KeyTyped)

		KeyTypedEvent(int keyCode) : KeyEvent(keyCode)
		{}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << keyCode;
			return ss.str();
		}
	};
}