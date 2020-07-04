#include "LayerStack.h"

namespace UGame
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : layers)
		{
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layers.emplace(layers.begin() + layerInsert, layer);
		layer->OnAttach();
		layerInsert++;
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(layers.begin(), layers.end(), layer);
		if (it != layers.end())
		{
			layers.erase(it);
			layer->OnDetach();
			layerInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(layers.begin(), layers.end(), overlay);
		if (it != layers.end())
		{
			overlay->OnDetach();
			layers.erase(it);
		}
	}
}

