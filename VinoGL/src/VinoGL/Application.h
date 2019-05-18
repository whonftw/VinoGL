#pragma once
#include "Core.h"
#include <memory>
namespace Vino {

	class VINO_API Application
	{
	public:
		Application();
		void Run();
	};

	std::unique_ptr<Application> CreateApplication();
}
