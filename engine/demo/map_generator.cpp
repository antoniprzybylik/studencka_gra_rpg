#include <algorithm>
#include <random>
#include <cstdint>

#include "map.h"
#include "block_codes.h"

static std::uniform_int_distribution<unsigned short> pick;
static std::random_device rd;
static std::default_random_engine re(rd());

void place_books(uint8_t *map, int width, int x)
{
	int y;
	int h;
	int i;

	y = 0;
	while (map[y*width+x] != 0)
		y++;

	h = pick(re)%3 + 2;

	for (i = 0; i < h; i++) {
		map[y*width+x] = BLOCK_BOOKS;
		map[y*width+x+1] = BLOCK_BOOKS;
		map[y*width+x-1] = BLOCK_BOOKS;
		y++;

	}

}

void place_flower(uint8_t *map, int width, int x)
{
	int y;
	int val;

	y = 0;
	while (map[y*width + x] != 0)
		y++;

	map[y*width + x] = BLOCK_DESK;

	if (pick(re) & 1)
		map[y*width + x] = BLOCK_DESK;

	if (map[y*width + x+1] == BLOCK_EMPTY &&
	    map[(y-1)*width + x+1] != BLOCK_EMPTY) {
		val = pick(re)%3;

		if (val == 0 || val == 1) {
			map[y*width + x+1] =
				map[y*width + x];
		}

		if (map[y*width + x+2] == BLOCK_EMPTY &&
		    map[(y-1)*width + x+2] != BLOCK_EMPTY) {
			val = pick(re)%3;

			if (val == 0) {
				map[y*width + x+2] =
					map[y*width + x];
			}
		}
	}
}

void place_cloud(uint8_t *map, int width, int x)
{
	int y;

	y = 0;
	while (map[y*width + x] != BLOCK_EMPTY)
		y++;

	if (pick(re) & 1) {
		map[(y+3)*width + x] = BLOCK_BOARD;
	} else {
		map[(y+2)*width + x] = BLOCK_BOARD;
	}
}

Map generate_map(int width, int height,
		 int max_dh, int flatness, int plants)
{
	int map_size = width*height;
	Map map(width, height);
	uint8_t *tab = map.get_map();

	int ac_height, delta_height;
	int tf;

	int i, j;

	for (i = 0; i < map_size; i++)
		tab[i] = BLOCK_EMPTY;

	ac_height = height/2;
	tf = 0;
	for (i = 0; i < width; i++) {
		if (pick(re)%flatness == BLOCK_EMPTY) {
			tf = 0;
			delta_height = (pick(re) % 2*max_dh+1) -
				       max_dh;
		} else {
			tf++;
			delta_height = 0;

			if (tf >= 5) {
				if (pick(re)%plants == 0) {
					tf=0;
					place_books(tab,
						   width,
						   i - 2);
				}
				else {
					if ((pick(re) & 1) == 0 || (pick(re) & 1) == 1 ) {
						tf = 0;
						place_cloud(tab,
							    width,
							    i - 2);
					}
				}
			} else {
				if ((pick(re) % 5*plants == 0) &&
				    tf >= 2) {
					tf = 0;
					place_flower(tab,
						     width,
						     i - 2);
				}
			}
		}

		ac_height += delta_height;

		j = 0;
		for ( ; j < ac_height; j++)
			tab[j*width + i] = BLOCK_FLOOR;
		tab[j*width + i] = BLOCK_FLOOR;
	}

	std::reverse(tab, tab + map_size+1);
	return map;
}
