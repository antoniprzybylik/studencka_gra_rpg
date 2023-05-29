#include <iostream>

#include "game.h"
#include "algebra.h"
#include "boss_sprite.h"

#include "player.h"
#include "enemy.h"
#include "question_ui.h"

BossSprite::BossSprite(std::shared_ptr<SpriteSkin> skin,
		       int x, int y, QuestionUI qui,
		       int z_order) :
Sprite(skin, z_order),
x(x),
y(y),
qui(qui)
{
}

void BossSprite::animate(void)
{
	if (Game::player_x > x + 1 &&
	    !hidden) {
		Game::player_x = x - 1;
		Game::player_y = y - 1;
		Game::sx = 0;
		Game::sy = 0;
	}

	set_position(Rect((this->x - Game::scroll_x)*Game::tile_size +
			  Game::shift_x - Game::player_width*Game::tile_size/2,
			  (this->y - Game::scroll_y)*Game::tile_size +
			  Game::shift_y - Game::player_height*Game::tile_size/2,
			  Game::player_width*Game::tile_size,
			  Game::player_height*Game::tile_size));
}

void BossSprite::on_click(void)
{
	qui.exec(Game::player_data);
	this->set_hidden(true);
}
