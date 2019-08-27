#include "vnpch.h"
#include "Application.h"
#include "Events/EventAggregator.h"
#include "Events/WindowEvents.h"
std::unique_ptr<Vino::Application> Vino::Application::s_Application;

Vino::Application::Application()
{
	m_Window = std::unique_ptr<Window>(Window::Create());
	m_ImGuiLayer = std::make_shared<ImGuiLayer>();
	s_Application = std::unique_ptr<Application>(this);
	
}

void Vino::Application::Run()
{
	PushOverlay(std::static_pointer_cast<Layer>(m_ImGuiLayer));

	auto WindowClosedEventToken = EventAggregator<WindowClosedEvent>::Subscribe([&](const WindowClosedEvent&)
	{
		m_IsOpen = false;
		VN_CORE_WARN("Application closed by user");
	});

	while (m_IsOpen) 
	{
		m_Window->OnUpdate();
		m_ImGuiLayer->Begin();
		for (auto& layer : m_LayerManager)
		{
			layer->OnRender();
		}
		m_ImGuiLayer->End();
	}
}

void Vino::Application::PushLayer(std::shared_ptr<Layer>& layer)
{
	m_LayerManager.AddLayer(layer);
	layer->OnAttach();
}

void Vino::Application::PushOverlay(std::shared_ptr<Layer>& layer)
{
	m_LayerManager.AddOverlay(layer);
	layer->OnAttach();
}

Vino::Application::~Application()
{

}
