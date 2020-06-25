#pragma once

#include "Crystal/Core.h"
#include "Layer.h"

namespace Crystal
{
	class CR_API LayerStack
	{
	public:

		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		unsigned int m_LayerInsertIndex = 0;

#pragma warning( push )
#pragma warning( disable : 4251 )
		std::vector<Layer*> m_Layers;
#pragma warning( pop )
	};
}