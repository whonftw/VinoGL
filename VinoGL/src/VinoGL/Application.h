#pragma once
#include "Core.h"
#include "Window.h"
#include <memory>
#include "LayerManager.h"
#include "VinoGL/ImGui/ImGuiLayer.h"
namespace Vino {

	class VINO_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();

		void PushLayer(std::shared_ptr<Layer>& layer);
		void PushOverlay(std::shared_ptr<Layer>& layer);
		static inline Application& Get() { return *s_Application.get(); }
		inline Window& GetWindow() { return *m_Window.get(); }
	private:
		std::unique_ptr<Window> m_Window;
		std::shared_ptr<ImGuiLayer> m_ImGuiLayer;

		bool m_IsOpen = true;
		LayerManager m_LayerManager;
		
		static std::unique_ptr<Application> s_Application;
	};

	std::unique_ptr<Application> CreateApplication();
}
