#pragma once
#include "vnpch.h"
#include "VinoGL.h"
#include "Layer.h"
namespace Vino
{
	class VINO_API LayerManager
	{
	public:
		LayerManager();
		~LayerManager();
		void AddLayer(std::shared_ptr<Layer>);
		void RemoveLayer(const std::shared_ptr<Layer>&);
		void AddOverlay(std::shared_ptr<Layer>);
		void RemoveOverlay(const std::shared_ptr<Layer>&);
		inline auto begin() noexcept{ return m_Layers.rbegin(); }
		inline auto end() noexcept { return m_Layers.rend(); }
		inline size_t size() const noexcept { return m_Layers.size(); }
	private:
		std::list<std::shared_ptr<Layer>> m_Layers;
		unsigned int m_InsertPosition = 0;
	};
}