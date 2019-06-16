#include "vnpch.h"
#include "Application.h"
#include "Events/EventAggregator.h"
#include "Events/WindowEvents.h"
Vino::Application::Application()
{
	m_Window = std::unique_ptr<Window>(Window::Create());
}

void Vino::Application::Run()
{
	auto WindowClosedEventToken = EventAggregator<WindowClosedEvent>::Subscribe([&](const WindowClosedEvent&)
	{
		m_IsOpen = false;
		VN_CORE_WARN("Application closed by user");
	});

	auto keyPressedToken = EventAggregator<KeyPressedEvent>::Subscribe([&](KeyPressedEvent& keyPressed)
	{
		for (auto& layer : m_LayerManager)
		{
			layer->OnKeyPressed(keyPressed);
			if (keyPressed.Handled)
				break;
		}
	});

	auto keyReleasedToken = EventAggregator<KeyReleasedEvent>::Subscribe([&](KeyReleasedEvent& keyReleased)
	{
		for (auto& layer : m_LayerManager)
		{
			layer->OnKeyReleased(keyReleased);
			if (keyReleased.Handled)
				break;
		}
	});

	auto keyTypedToken = EventAggregator<KeyTypedEvent>::Subscribe([&](KeyTypedEvent& keyTyped)
	{
		for (auto& layer : m_LayerManager)
		{
			layer->OnKeyTyped(keyTyped);
			if (keyTyped.Handled)
				break;
		}
	});

	auto mouseButtonPressedToken = EventAggregator<MouseButtonPressedEvent>::Subscribe([&](MouseButtonPressedEvent& mousePressed)
	{
		for (auto& layer : m_LayerManager)
		{
			layer->OnMouseButtonPressed(mousePressed);
			if (mousePressed.Handled)
				break;
		}
	});

	auto mouseButtonReleasedToken = EventAggregator<MouseButtonReleasedEvent>::Subscribe([&](MouseButtonReleasedEvent& mouseReleased)
	{
		for (auto& layer : m_LayerManager)
		{
			layer->OnMouseButtonReleased(mouseReleased);
			if (mouseReleased.Handled)
				break;
		}
	});

	auto mousePositionChangedToken = EventAggregator<MousePositionChangedEvent>::Subscribe([&](MousePositionChangedEvent& mousePositionChanged)
	{
		for (auto& layer : m_LayerManager)
		{
			layer->OnMousePositionChanged(mousePositionChanged);
			if (mousePositionChanged.Handled)
				break;
		}
	});

	auto mouseScrolledToken = EventAggregator<MouseScrolledEvent>::Subscribe([&](MouseScrolledEvent& mouseScrolled)
	{
		for (auto& layer : m_LayerManager)
		{
			layer->OnMouseScrolled(mouseScrolled);
			if (mouseScrolled.Handled)
				break;
		}
	});

	while (m_IsOpen) 
	{
		m_Window->OnUpdate();
		for (auto& layer : m_LayerManager)
		{
			layer->OnUpdate();
		}
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
