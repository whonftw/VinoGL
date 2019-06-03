#include "vnpch.h"
#include "LayerManager.h"

Vino::LayerManager::LayerManager()
{
}

Vino::LayerManager::~LayerManager()
{
}

void Vino::LayerManager::AddLayer(std::shared_ptr<Layer> layer)
{
	auto startPosition = m_Layers.begin();
	std::advance(startPosition, m_InsertPosition++);
	m_Layers.emplace(startPosition, layer);
}

void Vino::LayerManager::RemoveLayer(const std::shared_ptr<Layer>& layer)
{
	m_Layers.remove(layer);
}

void Vino::LayerManager::AddOverlay(std::shared_ptr<Layer> layer)
{
	m_Layers.emplace_back(layer);
}

void Vino::LayerManager::RemoveOverlay(const std::shared_ptr<Layer>& layer)
{
	m_Layers.remove(layer);
}
