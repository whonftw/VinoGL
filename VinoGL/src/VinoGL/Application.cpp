#include "vnpch.h"
#include "Application.h"
#include "Events/EventAggregator.h"
#include "Events/Window/WindowEvents.h"
Vino::Application::Application()
{
	m_Window = std::unique_ptr<Window>(Window::Create());
}

void Vino::Application::Run()
{
	auto subscriptionToken = EventAggregator<WindowClosed>::Subscribe([&](const WindowClosed&)
	{
		m_IsOpen = false;
		VN_CORE_WARN("Application closed by user");
	});
	while (m_IsOpen) 
	{
		m_Window->OnUpdate();
	}
}

Vino::Application::~Application()
{

}
