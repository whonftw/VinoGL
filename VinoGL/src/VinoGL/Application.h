#pragma once
#include "Core.h"
#include <memory>
#include "Window.h"

namespace Vino {

	class VINO_API Application
	{
	public:
		Application();
		void Run();
	private:
		std::unique_ptr<Window> m_Window;
	};

	std::unique_ptr<Application> CreateApplication();
}
