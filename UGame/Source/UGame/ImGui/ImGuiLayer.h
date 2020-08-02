#pragma once
#include "UGame/Layer.h"

namespace UGame
{
	class UGAME_API ImGuiLayer : public Layer
	{
	public:

		ImGuiLayer();

		static ImGuiLayer* Create();
		
		virtual void OnImGuiRender(ImGuiContext *const context) = 0;

		virtual void Begin() = 0;
		virtual void End() = 0;
	};
}