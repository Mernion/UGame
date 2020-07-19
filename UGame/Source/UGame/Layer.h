#pragma once
#include "Core/Timestep.h"
#include "UGame/Events/Event.h"

namespace UGame
{
	class UGAME_API Layer
	{
	public:

		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return debugName; }

	protected:

		std::string debugName;
	};

}

