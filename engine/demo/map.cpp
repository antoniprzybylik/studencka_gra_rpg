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

const std::shared_ptr<uint8_t[]>
Map::get_map(void) const noexcept
{
	return this->map;
}

uint8_t &Map::operator[](int index) noexcept
{
	return map[index];
}

Map &Map::operator=(Map &&map) & noexcept
{
	this->map = map.map;
	map.map = nullptr;

	this->width = map.width;
	this->height = map.height;

	return *this;
}
