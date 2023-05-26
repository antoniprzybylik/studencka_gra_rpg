#include <algorithm>
#include <random>
#include <cstdint>

#include "map.h"
#include "block_codes.h"

static std::uniform_int_distribution<unsigned short> pick;
static std::random_device rd;
static std::default_random_engine re(rd());

void place_books(Map &map, int x)
{
	int y;
	int h;
	int i;
	
	y = 0;
	while (map[y][x] != 0)
		y++;

	h = pick(re)%3 + 2;

	for (i = 0; i < h; i++) {
		map[y][x] = BLOCK_BOOKS;
		map[y][x+1] = BLOCK_BOOKS;
		map[y][x-1] = BLOCK_BOOKS;
		y++;
	}
}

void place_desk(Map &map, int x)
{
	int y;
	int val;
	
	y = 0;
	while (map[y][x] != 0)
		y++;
	
	map[y][x] = BLOCK_DESK;
	
	if (pick(re) & 1) {
		map[y][x] = BLOCK_DESK;
	} else {
		// TODO: Inny obiekt?
		//map[y][x] = BLOCK_DESK;
	}
	
	if (map[y][x+1] == BLOCK_EMPTY &&
	    map[(y-1)][x+1] != BLOCK_EMPTY) {
		val = pick(re)%3;
		
		if (val == 0 || val == 1)
			map[y][x+1] = map[y][x];
		
		if (map[y][x+2] == BLOCK_EMPTY &&
		    map[(y-1)][x+2] != BLOCK_EMPTY) {
			val = pick(re)%3;
			
			if (val == 0) {
				map[y][x+2] = map[y][x];
			}
		}
	}
}

void place_board(Map &map, int x)
{
	int y;
	
	y = 0;
	while (map[y][x] != BLOCK_EMPTY)
		y++;
	
	if (pick(re) & 1)
		map[(y+2)][x] = BLOCK_BOARD;
	else
		map[(y+3)][x] = BLOCK_BOARD;
}

Map generate_map(int width, int height,
		 int max_dh, int flatness, int desks)
{
	int map_size = width*height;
	Map map(width, height);
	
	int ac_height, delta_height;
	int tf;

	int i, j;

	for (i = 0; i < map_size; i++)
		map.tile(i) = BLOCK_EMPTY;
	
	ac_height = height/2;
	tf = 0;
	for (i = 0; i < width; i++) {
		if (pick(re)%flatness == 0) {
			tf = 0;
			delta_height = (pick(re) % 2*max_dh+1) -
				       max_dh;
		} else {
			tf++;
			delta_height = 0;

			if (tf >= 3)
			{
				if ((pick(re) & 1) == 0)
				{
					tf = 0;
					place_board(map,
						    i - 2);
				}
				else
				{
					if (pick(re)%desks == 0)
					{
						tf=0;
						place_books(map,
							    i - 2);
					}
				}
			}
			else
			{
				if ((pick(re) % 2*desks == 0) && tf >= 2)
				{
					tf = 0;
					place_desk(map,
						   i - 2);
				}
			}
		}

		ac_height += delta_height;
		
		j = 0;
		for ( ; j < ac_height; j++)
			map[j][i] = BLOCK_CONCRETE;
		map[j][i] = BLOCK_FLOOR;
	}
	
	std::reverse(map.get_map(),
		     map.get_map() + map_size+1);
	return map;
}
