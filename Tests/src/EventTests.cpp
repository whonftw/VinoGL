//#include "catch.hpp"
//#include "VinoGL.h"
//
//class StaticTest {
//public:
//	static void Test(int x)
//	{
//		VN_CLIENT_TRACE(x);
//	}
//};
//
//class MemberTest {
//public:
//	void Test(int x)
//	{
//		VN_CLIENT_TRACE(x);
//	}
//};
//
//TEST_CASE("Event subscribe with lambda")
//{
//	Vino::Logger::Init();
//	struct SimpleValue {
//		const char* value;
//	};
//	Vino::Logger::Init();
//	Vino::EventAggregator<SimpleValue>::Subscribe([](const SimpleValue& val) {
//		VN_CLIENT_TRACE(val.value);
//	});
//	Vino::EventAggregator<SimpleValue>::Subscribe([](const SimpleValue& val) {
//		//VN_CLIENT_TRACE(val.value);
//	});
//	REQUIRE(Vino::EventAggregator<SimpleValue>::Publish({ "Lambda" }));
//}
//
//TEST_CASE("Event subscribe with static class member")
//{
//	Vino::EventAggregator<int>::Subscribe(&StaticTest::Test);
//	REQUIRE(Vino::EventAggregator<int>::Publish(1));
//}
//
//TEST_CASE("Event clear test")
//{
//	Vino::EventAggregator<int>::ClearSubscriptions();
//	REQUIRE(!Vino::EventAggregator<int>::Publish(0));
//}
//
//TEST_CASE("Event subscribe with class member")
//{
//	MemberTest mb;
//	Vino::EventAggregator<int>::Subscribe(std::bind(&MemberTest::Test, &mb, std::placeholders::_1));
//	Vino::EventAggregator<int>::Publish(2);
//}
//
