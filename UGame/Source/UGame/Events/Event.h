#pragma once
#include "UGame/Core.h"
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
								const char* GetName() const override {return #type; }

#define BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)
		
// TODO:: find some generic way to handle a lot of events? maybe more polymorphic types?
// macros? or just some third party library for all this stuff;

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

		inline bool getHandled() const { return handled; }

	protected:

		bool handled = false;
	};


	// implement: bool func(Event& ev) somewhere in the class that handles event
	// and dispatch event by event dispatcher
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:

		EventDispatcher(Event& newEvent) : currEvent(newEvent) {}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (currEvent.GetEventType() == T::GetStaticType())
			{
				currEvent.handled = func(*(T*)&currEvent);
				return true;
			}
			return false;
		}
		
	private:
		Event& currEvent;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& ev)
	{
		return os << ev.ToString();
	}
}

