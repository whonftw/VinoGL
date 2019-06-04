#include "catch.hpp"
#include "VinoGL.h"

struct SimpleValue: Vino::PublicEvent {
	const char* value;
	SimpleValue(const char* val): value(val)
	{
			
	}
};

class StaticTest {
public:
	static void Test(SimpleValue x)
	{
		VN_CLIENT_TRACE("{0}", x.value);
	}
};

class MemberTest {
	int xInt;
public:
	MemberTest(int x): xInt(x) { }
	void Test(SimpleValue x)
	{
		VN_CLIENT_TRACE("{0}:{1}", xInt, x.value);
	}
};
TEST_CASE("Event subscribe with lambda")
{
	Vino::Logger::Init();

	auto subscriptionToken = Vino::EventAggregator<SimpleValue>::Subscribe([](const SimpleValue& val) {
			VN_CLIENT_TRACE("{0}", val.value);
		})
	;
	REQUIRE(Vino::EventAggregator<SimpleValue>::Publish({ "Hello from lambda" }));
}

TEST_CASE("Event check if previous subscription has been removed")
{
	REQUIRE(!Vino::EventAggregator<SimpleValue>::Publish({ "asdf" }));
}

TEST_CASE("Event with static method")
{
	auto subscriptionToken = Vino::EventAggregator<SimpleValue>::Subscribe(&StaticTest::Test);
	REQUIRE(Vino::EventAggregator<SimpleValue>::Publish({ "Hello from class static method" }));
}

TEST_CASE("Event with member function of object")
{
	MemberTest test(1);
	auto subscriptionToken = Vino::EventAggregator<SimpleValue>::Subscribe(std::bind(&MemberTest::Test, &test, std::placeholders::_1));
	REQUIRE(Vino::EventAggregator<SimpleValue>::Publish("Hello from member function of object"));
}


TEST_CASE("Order test")
{
	int x = 1;
	auto subscriptionToken1 = Vino::EventAggregator<SimpleValue>::Subscribe([&](const SimpleValue& val) {
		REQUIRE(x++ == 1);
	});
	auto subscriptionToken2 = Vino::EventAggregator<SimpleValue>::Subscribe([&](const SimpleValue& val) {
		REQUIRE(x++ == 2);
	});
	auto subscriptionToken3 = Vino::EventAggregator<SimpleValue>::Subscribe([&](const SimpleValue& val) {
		REQUIRE(x++ == 3);
	});
	Vino::EventAggregator<SimpleValue>::Publish({"value"});
}
