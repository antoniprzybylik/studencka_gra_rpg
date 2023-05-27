#include <iostream>
#include <cmath>

#include "game.h"
#include "block_codes.h"
#include "tile_sprite.h"

void TileSprite::translate(int tx, int ty)
{
	x += tx;
	y += ty;

	if (x < 0 || !(x < Game::map_width)) {
		index = 0;
	} else {
		if (y < 0 || !(y < Game::map_height)) {
			index = 0;
			block_id = 0;
		} else {
			index = y*Game::map_width + x;
		}
	}
}

void TileSprite::animate(void)
{
	int rel_shift_x, rel_shift_y;

	while (x - Game::scroll_x < -Game::screen_x/2)
		translate(Game::screen_x, 0);

	while (x - Game::scroll_x > Game::screen_x/2)
		translate(-Game::screen_x, 0);

	while (y - Game::scroll_y < -Game::screen_y/2)
		translate(0, Game::screen_y);

	while (y - Game::scroll_y > Game::screen_y/2)
		translate(0, -Game::screen_y);

	if (index > 0)
		block_id = Game::map.tile(index);
	else
		block_id = BLOCK_EMPTY;

	if (block_id > 0) {
		rel_shift_x = Game::tile_data[block_id].shift_x;
		rel_shift_y = Game::tile_data[block_id].shift_y;

		Rect pos = position;
		pos.set_pos_x((x - Game::scroll_x)*Game::tile_size +
			      Game::shift_x + rel_shift_x - Game::tile_size/2);
		pos.set_pos_y((y - Game::scroll_y)*Game::tile_size +
			      Game::shift_y + rel_shift_y - Game::tile_size/2);
		set_position(pos);

		static_pointer_cast<TextureSkin>(skin)->
				request_frame(block_id);
		set_hidden(false);
	} else {
		set_hidden(true);
	}
}

void TileSprite::on_click(void)
{
	std::cerr << position.get_pos_x() << ", "
		  << position.get_pos_y() << std::endl;

	std::cerr << "index: " << index << std::endl;
	std::cerr << "block_id: " << block_id << std::endl;
	std::cerr << "hidden: " << hidden << std::endl;

	/* TODO: Może coś w tym miejscu narysować? */
}

TileSprite::TileSprite(std::shared_ptr<TextureSkin> &skin, Rect bounds,
		       enum bounds_action bounds_action,
		       int z_order) :
Sprite(std::static_pointer_cast<SpriteSkin>(skin), bounds, bounds_action, z_order)
{
}

TileSprite::~TileSprite(void)
{
}
