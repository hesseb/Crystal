#pragma once

#include "Crystal/Core/Core.h"
#include "Crystal/Core/Layer.h"

#include <vector>

namespace Crystal
{
	class LayerStack
	{
	public:

		LayerStack() = default;
		~LayerStack();

		void PushLayer(Ref<Layer> layer);
		void PopLayer(Ref<Layer> layer);
		void PushOverlay(Ref<Layer> overlay);
		void PopOverlay(Ref<Layer> overlay);

		std::vector<Ref<Layer>>::iterator begin() { return m_Layers.begin(); }
		std::vector<Ref<Layer>>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Ref<Layer>> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}