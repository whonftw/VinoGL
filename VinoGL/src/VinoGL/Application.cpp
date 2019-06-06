#include "vnpch.h"
#include "Application.h"
#include "Events/EventAggregator.h"
#include "Events/Window/WindowEvents.h"
Vino::Application::Application()
{
	m_Window = std::unique_ptr<Window>(Window::Create());
	EventAggregator<WindowClosed>::Subscribe([&](const WindowClosed&)
	{
		m_IsOpen = false;
		VN_CORE_WARN("Application closed by user");
	});
}

void Vino::Application::Run()
{
	while (m_IsOpen) 
	{
		m_Window->OnUpdate();
		for (const auto& layer : m_LayerManager)
		{
			layer->OnUpdate();
		}
	}
}

void Vino::Application::PushLayer(std::shared_ptr<Layer>& layer)
{
	m_LayerManager.AddLayer(layer);
}

void Vino::Application::PushOverlay(std::shared_ptr<Layer>& layer)
{
	m_LayerManager.AddOverlay(layer);
}

Vino::Application::~Application()
{

}
