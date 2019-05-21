#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "VinoGL/Logger.h"

TEST_CASE("Loggers are valid after initialization", "[init]")
{
	Vino::Logger::Init();
	REQUIRE(Vino::Logger::GetClientLogger());
	REQUIRE(Vino::Logger::GetCoreLogger());
}