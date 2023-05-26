#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <cstdint>

#include "map.h"
#include "tile_data.h"

extern const double x_vel;
extern const double y_vel;

extern double map_height, map_width;
extern Map map;
extern std::unique_ptr<tile_data_t[]> tile_data;

extern double player_width, player_height;
extern double tile_size;
extern double screen_x, screen_y;

extern double scroll_x, scroll_y;
extern double player_x, player_y;
extern double sx, sy;
extern double shift_x, shift_y;

#endif /* GAME_H_ */
