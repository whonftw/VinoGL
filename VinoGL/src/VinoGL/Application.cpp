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
	}
}

Vino::Application::~Application()
{

}
