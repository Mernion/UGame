#pragma once

#include "../Core.h"

#include <string>
#include <functional>

namespace UGame
{
	// current event system is "blocking" (when event occurs it immediately gets processed). 
	// TODO:: create some sort of buffer to queue events and process them
	// when we need to

	enum class EventType
	{
		None,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum class  EventCategory
	{
		None = 0,
		Application = BIT(0), //  1 << x
		Input = BIT(1),
		Keyboard = BIT(2),
		Mouse = BIT(3),
		MouseButton = BIT(4)
	};

// helper macros to generate boilerplate overrides; TODO:: maybe there is better way to handle this?
// some sort of reflection system should help here;

#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() {return EventType::##type; }\
								EventType GetEventType() const override {return GetStaticType(); }\
								const char* GetName() const override {return ##type; }
									
	class UGAME_API Event
	{
		friend class EventDispatcher;
	public:

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }
		
		inline bool IsInCategory(EventCategory category) const
		{
			return GetCategoryFlags() & static_cast<int>(category);
		}

	protected:

		bool consumed = false;
	};

	class EventDispatcher
	{
		;
	};
}

