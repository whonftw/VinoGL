#pragma once
#include "Core.h"
#include <memory>
#include "Window.h"

namespace Vino {

	class VINO_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_IsOpen = true;
	};

	std::unique_ptr<Application> CreateApplication();
}
