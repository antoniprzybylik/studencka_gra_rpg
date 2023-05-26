#ifndef MAP_H_
#define MAP_H_

#include <cstdint>

class Map {
private:
	uint8_t *map;
	int width, height;

public:
	Map(void) noexcept;
	Map(int width, int height);
	Map(Map&&) noexcept;
	Map(const Map&);
	~Map(void);

	int get_width(void) const noexcept;
	int get_height(void) const noexcept;
	uint8_t *const get_map(void) const noexcept;

	uint8_t &operator[](int index) noexcept;
	Map &operator=(Map&&) & noexcept;
};

Map generate_map(int width, int height,
		 int max_dh, int flatness = 1, int plants = 3);

#endif  /* MAP_H_ */
