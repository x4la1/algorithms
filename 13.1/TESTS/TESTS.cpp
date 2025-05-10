#include "13.1/13.1/13.1.h"
#include <catch2/catch.hpp>

TEST_CASE("1")
{
	std::vector<std::pair<uint32_t, uint32_t>> expectedResult{ { 1, 1 }, { 1, 24 } };

	auto result = FindSubstring("mama mila ramu", "test1.txt");
	REQUIRE(expectedResult.size() == result.size());
	for (auto i = 0; i < result.size(); ++i)
	{
		CHECK(expectedResult[i].first == result[i].first);
		CHECK(expectedResult[i].second == result[i].second);
	}
}
