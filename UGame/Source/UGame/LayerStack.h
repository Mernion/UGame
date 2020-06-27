#pragma once
#include "Layer.h"

namespace UGame
{

	// overlayer's are always in the end, usuall layers are first (useful for render)
	class UGAME_API LayerStack
	{
	public:

		LayerStack();
		virtual ~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator end() { return layers.end(); }

	private:
		std::vector<Layer*> layers;
		std::vector<Layer*>::iterator layerInsert;
	};
}