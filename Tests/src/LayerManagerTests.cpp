#include "catch.hpp"
#include "VinoGL.h"
#include "VinoGL/LayerManager.h"

TEST_CASE("Add then remove size = 0")
{
	Vino::LayerManager lm;
	auto lsp1 = std::shared_ptr<Vino::Layer>(new Vino::Layer{ "l1" });
	lm.AddLayer(lsp1);
	REQUIRE(lm.size() == 1);
	lm.RemoveLayer(lsp1);
	REQUIRE(lm.size() == 0);
}