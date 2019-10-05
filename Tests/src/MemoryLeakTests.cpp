#include "vnpch.h"
#include "catch.hpp"
#include <memory>
#include "VinoGL.h"

TEST_CASE("Window memory leak test")
{
	bool exceptionThrown = false;
	try
	{
		{
			auto window = std::unique_ptr<Vino::Window>(Vino::Window::Create());
			VN_CLIENT_TRACE("Created Window");
		}
		VN_CLIENT_WARN("Window Destructed");
	}
	catch (std::exception& exception)
	{
		VN_CLIENT_CRITICAL("Exception thrown on Window Destruction");
		exceptionThrown = true;
	}
	REQUIRE(exceptionThrown == false);
}

TEST_CASE("LayerManager memory leak test")
{
	bool exceptionThrown = false;
	try
	{
		{
			Vino::LayerManager manager;
			auto layer = std::make_shared<Vino::Layer>("Custom Layer");
			manager.AddLayer(layer);
			VN_CLIENT_TRACE("Created Layer Manager and added layer");
		}
		VN_CLIENT_WARN("Layer Manager destructed");
	}
	catch (std::exception& exception)
	{
		VN_CLIENT_CRITICAL("Exception thrown on LayerManager destructed");
		exceptionThrown = true;
		
	}
	REQUIRE(exceptionThrown == false);
}

class CustomApplication : public Vino::Application
{
public:
	CustomApplication()
	{

	}
};

std::unique_ptr<Vino::Application> CreateApplication()
{
	std::unique_ptr<CustomApplication> customApplication(new CustomApplication());
	return std::move(customApplication);
}

TEST_CASE("Application memory leak test")
{
	bool exceptionThrown = false;
	try
	{
		{
			std::unique_ptr<Vino::Application> application = CreateApplication();
		}
	}
	catch (std::exception& exception)
	{
		exceptionThrown = true;
	}
	REQUIRE(exceptionThrown == false);
}