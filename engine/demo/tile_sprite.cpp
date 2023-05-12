#include <cmath>

#include "game.h"
#include "block_codes.h"
#include "tile_sprite.h"

void TileSprite::translate(int tx, int ty)
{
	x += tx;
	y += ty;

	if (x < 0 || !(x < map_width)) {
		index = 0;
	} else {
		if (y < 0 || !(y < map_height)) {
			index = 0;
			block_id = 0;
		} else {
			index = y*map_width + x;
		}
	}
}

void TileSprite::animate(void)
{
	int rel_shift_x, rel_shift_y;

	while (x - scroll_x < -screen_x/2)
		translate(screen_x, 0);

	while (x - scroll_x > screen_x/2)
		translate(-screen_x, 0);

	while (y - scroll_y < -screen_y/2)
		translate(0, screen_y);

	while (y - scroll_y > screen_y/2)
		translate(0, -screen_y);

	if (index > 0)
		block_id = map[index];
	else
		block_id = BLOCK_EMPTY;

	if (block_id > 0) {
		rel_shift_x = tile_data[block_id].shift_x;
		rel_shift_y = tile_data[block_id].shift_y;

		Rect pos = position;
		pos.set_pos_x((int) ((x - scroll_x)*tile_size) +
			      shift_x + rel_shift_x - tile_size/2);
		pos.set_pos_y((int) ((y - scroll_y)*tile_size) +
			      shift_y + rel_shift_y - tile_size/2);
		set_position(pos);

		static_pointer_cast<TextureSkin>(skin)->
				request_frame(block_id);
		set_hidden(false);
	} else {
		set_hidden(true);
	}
}

#include <iostream>

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
