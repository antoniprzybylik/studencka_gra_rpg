#include "game.h"
#include "algebra.h"
#include "player_sprite.h"

PlayerSprite::PlayerSprite(std::shared_ptr<SpriteSkin> skin,
			   int z_order) :
Sprite(skin, z_order)
{
}

void PlayerSprite::animate(void)
{
	set_position(Rect((Game::player_x-Game::scroll_x)*Game::tile_size +
			  Game::shift_x - Game::player_width*Game::tile_size/2,
			  (Game::player_y - Game::scroll_y)*Game::tile_size +
			  Game::shift_y - Game::player_height*Game::tile_size/2,
			  Game::player_width*Game::tile_size,
			  Game::player_height*Game::tile_size));
}
