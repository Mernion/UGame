#pragma once

#include "Event.h"

namespace UGame
{
	class UGAME_API WindowResizeEvent : public Event
	{
	public:
		
	EVENT_CLASS_TYPE(WindowResize)

	WindowResizeEvent(unsigned int width, unsigned int height) : width(width), height(height) {}

	inline unsigned int GetWidth() const { return width; }
	inline unsigned int GetHeight() const { return height; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "WindowResizeEvent: " << width << " , " << height;
		return ss.str();
	}

	int GetCategoryFlags() const override
	{
		return static_cast<int>(EventCategory::Application);
	}

	private:
		unsigned int width, height;
	};

	class UGAME_API WindowCloseEvent : public Event
	{
	public:
		
		EVENT_CLASS_TYPE(WindowClose)

		WindowCloseEvent() {}

		int GetCategoryFlags() const override
		{
			return static_cast<int>(EventCategory::Application);
		}
	};

	class UGAME_API AppTickEvent : public Event
	{
	public:

		EVENT_CLASS_TYPE(AppTick)

		AppTickEvent() {}

		int GetCategoryFlags() const override
		{
			return static_cast<int>(EventCategory::Application);
		}

	};

	class UGAME_API AppUpdateEvent : public Event
	{
	public:

		EVENT_CLASS_TYPE(AppUpdate)

		AppUpdateEvent() {}

		int GetCategoryFlags() const override
		{
			return static_cast<int>(EventCategory::Application);
		}
	};

	class UGAME_API AppRenderEvent : public Event
	{
	public:

		EVENT_CLASS_TYPE(AppRender)

		AppRenderEvent() {}

		int GetCategoryFlags() const override
		{
			return static_cast<int>(EventCategory::Application);
		}

	};
}