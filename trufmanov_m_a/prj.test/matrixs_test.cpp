#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>


TEST_CASE("first test"){
	SUBCASE("first first test"){
		CHECK(1 == 1);
	}
}
