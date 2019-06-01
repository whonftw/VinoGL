#include "vnpch.h"
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

TEST_CASE("Proper order on iteration")
{
	Vino::LayerManager lm;
	auto lsp1 = std::shared_ptr<Vino::Layer>(new Vino::Layer{ "l1" });
	auto lsp2 = std::shared_ptr<Vino::Layer>(new Vino::Layer{ "l2" });
	auto olsp1 = std::shared_ptr<Vino::Layer>(new Vino::Layer{ "ol1" });
	auto olsp2 = std::shared_ptr<Vino::Layer>(new Vino::Layer{ "ol2" });
	lm.AddLayer(lsp1);
	lm.AddOverlay(olsp1);
	lm.AddLayer(lsp2);
	lm.AddOverlay(olsp2);
	auto it = lm.begin();
	REQUIRE((*it)->Name == "ol2");
	it++;
	REQUIRE((*it)->Name == "ol1");
	it++;
	REQUIRE((*it)->Name == "l2");
	it++;
	REQUIRE((*it)->Name == "l1");
}

TEST_CASE("Lifetime test")
{
	Vino::LayerManager lm;
	{
		auto lsp1 = std::shared_ptr<Vino::Layer>(new Vino::Layer{ "l1" });
		lm.AddLayer(lsp1);
	}
	REQUIRE(lm.size() != 0);
}