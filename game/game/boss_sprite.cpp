#include "game.h"
#include "algebra.h"
#include "boss_sprite.h"

BossSprite::BossSprite(std::shared_ptr<SpriteSkin> skin,
		       int x, int y, int z_order) :
Sprite(skin, z_order),
x(x),
y(y)
{
}

void BossSprite::animate(void)
{
	set_position(Rect((this->x - Game::scroll_x)*Game::tile_size +
			  Game::shift_x - Game::player_width*Game::tile_size/2,
			  (this->y - Game::scroll_y)*Game::tile_size +
			  Game::shift_y - Game::player_height*Game::tile_size/2,
			  Game::player_width*Game::tile_size,
			  Game::player_height*Game::tile_size));
}
