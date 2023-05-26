#include<memory>

#include "game.h"

const double x_vel = 5.0;
const double y_vel = 0.2;

double map_height, map_width;
Map map;
std::unique_ptr<tile_data_t[]> tile_data(nullptr);

double player_width, player_height;
double tile_size;
double screen_x, screen_y;

double scroll_x, scroll_y;
double player_x, player_y;
double sx, sy;
double shift_x, shift_y;
