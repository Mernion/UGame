#pragma once
#include "imgui.h"
#include "imgui_internal.h"
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
		virtual void OnImGuiRender(ImGuiContext* const context) {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return debugName; }

	protected:

		std::string debugName;
	};

}

