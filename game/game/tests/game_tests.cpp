#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <json/json.h>
#include <json/value.h>

#include "map.h"

TEST_CASE("map")
{
	int i;

	Map map = generate_map(8, 3, 3, 1, 1);
	Map map2;

	Json::Value root = map.dump();
	map2.load(root);

	for (i = 0; i <= map.get_width() *
			 map.get_height(); i++) {
		CHECK(map.tile(i) == map2.tile(i));
	}
}
