#ifndef MAP_H_
#define MAP_H_

#include <memory>
#include <cstdint>

class Map {
private:
	std::shared_ptr<uint8_t[]> map;
	int width, height;

public:
	Map(void) noexcept;
	Map(int width, int height);
	Map(Map&&) noexcept;
	Map(const Map&);
	~Map(void);

	int get_width(void) const noexcept;
	int get_height(void) const noexcept;
	uint8_t &tile(int index) noexcept {return map[index];};

	uint8_t *get_map(void) {return map.get();};

	class MapSliceReference {
	private:
		uint8_t *const map_slice;
		const int width;
	
	public:
		MapSliceReference(uint8_t *const map_slice,
				  const int width) :
			map_slice(map_slice),
			width(width) {}
	
		uint8_t &operator[](int index)
		{
			if (index >= width) {
				throw std::invalid_argument(
					"Index out of range.");
			}

			return map_slice[index];
		}
	};

	MapSliceReference operator[](int index)
	{
		if (index >= height) {
			throw std::invalid_argument(
				"Index out of range.");
		}

		return MapSliceReference(&map[index*width],
					 width);
	}

	Map &operator=(Map&&) & noexcept;
};

Map generate_map(int width, int height,
		 int max_dh, int flatness = 1, int plants = 3);

#endif  /* MAP_H_ */
