#include <algorithm>

#include "map.h"

Map::Map(void) noexcept :
map(nullptr),
width(0),
height(0)
{
}

Map::Map(int width, int height) :
map(std::make_shared<uint8_t[]>(width*height + 1)),
width(width),
height(height)
{
}

Map::Map(const Map &map) :
map(std::make_shared<uint8_t[]>(map.width*map.height + 1)),
width(map.width),
height(map.height)
{
	std::copy(map.map.get(),
		  map.map.get() +
		  map.width*map.height + 1,
		  this->map.get());
}

Map::Map(Map &&map) noexcept :
map(map.map),
width(map.width),
height(map.height)
{
	map.map = nullptr;
}

Map::~Map(void)
{
}

int Map::get_width(void) const noexcept
{
	return this->width;
}

int Map::get_height(void) const noexcept
{
	return this->height;
}

Map &Map::operator=(Map &&map) & noexcept
{
	this->map = map.map;
	map.map = nullptr;

	this->width = map.width;
	this->height = map.height;

	return *this;
}

Json::Value Map::dump(void) const
{
	int i;
	Json::Value d_root;
	Json::Value &d_map = d_root["map"];

	d_root["width"] = width;
	d_root["height"] = height;

	for (i = 0; i < width*height+1; i++)
		d_map.append(static_cast<int>(map[i]));

	return d_root;
}

void Map::load(Json::Value &d_root)
{
	int width, height;
	int i;

	if (!d_root.isObject()) {
		throw std::invalid_argument(
			"Corrupted data: "
			"Not an object.");
	}

	Json::Value &d_width = d_root["width"];
	Json::Value &d_height = d_root["height"];
	Json::Value &d_map = d_root["map"];

	if (!d_map.isArray()) {
		throw std::invalid_argument(
			"Corrupted data: "
			"Not an array.");
	}

	if (!d_width.isNumeric()) {
		throw std::invalid_argument(
			"Corrupted data: "
			"Not a value.");
	}
	width = d_width.asInt();

	if (!d_height.isNumeric()) {
		throw std::invalid_argument(
			"Corrupted data: "
			"Not a value.");
	}
	height = d_height.asInt();

	if (d_map.size() != (size_t) (width*height+1)) {
		throw std::invalid_argument(
			"Corrupted data: "
			"Wrong array size.");
	}

	map = std::make_shared<uint8_t[]>(d_map.size());
	for (i = 0; (size_t) i < d_map.size(); i++) {
		if (!d_map[i].isNumeric()) {
			throw std::invalid_argument(
				"Corrupted data: "
				"Not a value.");
		}

		map[i] = d_map[i].asInt();
	}
}
