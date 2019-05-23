#include "vnpch.h"
#include "Application.h"

Vino::Application::Application()
{
	m_Window = std::unique_ptr<Window>(Window::Create());
}

void Vino::Application::Run()
{
	while (true) 
	{
		m_Window->OnUpdate();
	}
}
