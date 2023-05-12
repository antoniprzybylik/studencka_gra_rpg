#include <algorithm>
#include <random>
#include <cstdint>

#include "map.h"
#include "block_codes.h"

static std::uniform_int_distribution<unsigned short> pick;
static std::random_device rd;
static std::default_random_engine re(rd());

void place_tree(uint8_t *map, int width, int x)
{
	int y;
	int h;
	int i, j;
	
	y = 0;
	while (map[y*width+x] != 0)
		y++;
	
	h = pick(re)%3 + 3;
	
	if (pick(re) & 1) {
		for (i = 3; i <= h+2; i++) {
			for (j = 0; j < i; j++){
				map[(y+h+5-i)*width +
				    x +
				    i - j - 1 - i/2] = BLOCK_LEAFS;
			}
		}
	} else {
		for (i = 3; i <= h+2; i++) {
			for (j = 0; j < i; j++) {
				map[(y+h+5-i)*width +
				    x + i - j - i/2 -
				    (pick(re)%3)] = BLOCK_LEAFS;
			}
		}
	}
	
	for (i = 0; i < h; i++) {
		map[y*width+x] = BLOCK_WOOD;
		y++;
	}
	
	map[y*width+x] = BLOCK_LEAFS;
	map[y*width+x+1] = BLOCK_LEAFS;
	map[y*width+x-1] = BLOCK_LEAFS;
	map[(y-1)*width+x+1] = BLOCK_LEAFS;
	map[(y-1)*width+x-1] = BLOCK_LEAFS;
	
	for (i = 1; i <= h-3; i++) {
		map[(y-i-1)*width+x+1] = BLOCK_LEAFS;
		map[(y-i-1)*width+x-1] = BLOCK_LEAFS;
	}
}

void place_flower(uint8_t *map, int width, int x)
{
	int y;
	int val;
	
	y = 0;
	while (map[y*width + x] != 0)
		y++;
	
	map[y*width + x] = BLOCK_YFLR;
	
	if (pick(re) & 1)
		map[y*width + x] = BLOCK_YFLR;
	else
		map[y*width + x] = BLOCK_RFLR;
	
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
		map[(y+4)*width + x] = BLOCK_RDCLD;
		map[(y+5)*width + x] = BLOCK_RUCLD;
		map[(y+4)*width + x+1] = BLOCK_LDCLD;
		map[(y+5)*width + x+1] = BLOCK_LUCLD;
	} else {
		map[(y+5)*width + x] = BLOCK_RDCLD;
		map[(y+6)*width + x] = BLOCK_RUCLD;
		map[(y+5)*width + x+1] = BLOCK_LDCLD;
		map[(y+6)*width + x+1] = BLOCK_LUCLD;
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
					place_tree(tab,
						   width,
						   i - 2);
				} else {
					if ((pick(re) & 1) == 0) {
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
			tab[j*width + i] = BLOCK_DIRT;
		tab[j*width + i] = BLOCK_GRASS;
	}
	
	std::reverse(tab, tab + map_size+1);
	return map;
}
