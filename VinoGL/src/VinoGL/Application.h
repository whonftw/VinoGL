#pragma once
#include "vnpch.h"
#include "Core.h"
#include "Window.h"
#include "LayerManager.h"
namespace Vino {

	class VINO_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();

		void PushLayer(std::shared_ptr<Layer>& layer);
		void PushOverlay(std::shared_ptr<Layer>& layer);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_IsOpen = true;
		LayerManager m_LayerManager;
	};

	std::unique_ptr<Application> CreateApplication();
}
