#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <cstdint>

#include "map.h"
#include "engine.h"
#include "tile_data.h"

#include "player.h"

class Game {
private:
	static std::unique_ptr<Engine> engine;

	static
	tile_info_t check_tile(int x, int y);
	static
	tile_info_t check_tiles(int x1, int y1,
				int x2, int y2);
	static void handle_keys(void);
	static void move_player(void);
	static void on_tick(void);
	static void prepare_game(std::unique_ptr<Engine> &engine);
	static std::unique_ptr<Engine> game_init(void);

public:
	static constexpr double x_vel = 5.0;
	static constexpr double y_vel = 0.2;
	
	static constexpr double map_height = 100.0;
	static constexpr double map_width = 100.0;
	
	static constexpr double player_width = 0.5;
	static constexpr double player_height = 1.0;
	static constexpr double tile_size = 80;
	static constexpr double screen_x = 17.0;
	static constexpr double screen_y = 10.0;

	static constexpr double shift_x = 640;
	static constexpr double shift_y = 360;

	static Map map;
	static std::unique_ptr<tile_data_t[]> tile_data;
	
	static double scroll_x;
	static double scroll_y;
	static double player_x;
	static double player_y;
	static double sx;
	static double sy;

	static Player player_data;

	Game(void) = delete;
	static void init(void);
	static void exec(void);
};

#endif /* GAME_H_ */
