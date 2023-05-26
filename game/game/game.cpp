#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

#include "engine.h"
#include "sprite.h"
#include "sprite_skin.h"
#include "game_window.h"
#include "algebra.h"
#include "time_utils.h"

#include "map.h"
#include "tile_data.h"
#include "game.h"

#include "tile_sprite.h"
#include "label_sprite.h"

tile_info_t Game::check_tile(int x, int y)
{
	int index = 0;
	int hard = 0;
	int above = 0;

	index = y*map_width+x;
	if ((x < 0) || (x >= map_width)) {
		hard = 0;
	} else {
		if ((y < 0) || (y >= map_height)) {
			hard = 0;
		} else {
			hard = map.tile(index);
			if (hard > 0) {
				hard = tile_data[hard].hard;
				index += map_width;
				above = tile_data[
					   map.tile(index)].hard;
			}
		}
	}

	return ((tile_info_t) {hard, index, above});
}

tile_info_t Game::check_tiles(int x1, int y1,
			      int x2, int y2)
{
	tile_info_t tile_info;

	tile_info = check_tile(x1, y1);
	if (tile_info.hard == 0)
		return check_tile(x2, y2);

	return tile_info;
}

void Game::handle_keys(void)
{
	tile_info_t tile_info;

	if (sf::Keyboard::
		isKeyPressed(sf::Keyboard::Left)) {
		sx = -x_vel / tile_size;
	} else {
		if (sf::Keyboard::
			isKeyPressed(sf::Keyboard::Right)) {
			sx = x_vel / tile_size;
		} else {
			sx = 0;
		}
	}

	if (sf::Keyboard::
		isKeyPressed(sf::Keyboard::Up)) {
		tile_info = check_tiles(player_x + player_width/2,
					player_y + 1,
					player_x + player_width + player_width/2,
					player_y+1);

		if (tile_info.hard)
			sy = y_vel;
	}
}

void Game::move_player(void)
{
	tile_info_t tile_info;

	player_x += sx;

	if (sx < 0) {
		tile_info = check_tiles(player_x + player_width/2,
					player_y,
					player_x + player_width + player_width/2,
					player_y - player_height);

		if (tile_info.hard) {
			player_x = std::ceil(player_x);
			player_x -= 0.5 - player_width/2;
			sx = 0;
		}
	} else if (sx > 0) {
		tile_info = check_tiles(player_x + player_width + player_width/2,
					player_y,
					player_x + 2*player_width + player_width/2,
					player_y - player_height);

		if (tile_info.hard > 0) {
			player_x = (int) player_x;
			player_x += 0.5 - player_width/2;
			sx = 0;
		}
	}

	sy = (sy-0.005)*0.99;
	player_y -= sy;
	
	if (sy < 0) {
		tile_info = check_tiles(player_x + player_width/2,
					player_y+1,
					player_x + player_width + player_width/2,
					player_y+1);

		if (tile_info.hard) {
			player_y = int(player_y);
			sy = 0;
		}
	} else {
		tile_info = check_tiles(player_x + player_width/2,
					player_y + player_height,
					player_x + player_width + player_width/2,
					player_y - player_height);

		if (tile_info.hard) {
			player_y = int(player_y);
			sy = 0;
		}
	}
}

static
const int ticks_in_frame = 17;

static std::string position_str("position: (-, -)");

static std::shared_ptr<LabelSprite> label_sprite(nullptr);
static std::shared_ptr<Sprite> player_sprite(nullptr);

void Game::on_tick(void)
{
	scroll_x = (player_x + scroll_x*11)/12;
	scroll_y = (player_y + scroll_y*11)/12;

	handle_keys();
	move_player();

	player_sprite->set_position(Rect(
			(player_x-scroll_x)*tile_size +
			shift_x - player_width*tile_size/2,
			(player_y - scroll_y)*tile_size +
			shift_y - player_height*tile_size/2,
			player_width*tile_size,
			player_height*tile_size));

	/* TODO */

	position_str = std::string("position: (") +
		       std::to_string(player_x) +
		       std::string(", ") +
		       std::to_string(player_y) +
		       std::string(")");
}

void Game::prepare_game(std::unique_ptr<Engine> &engine)
{
	std::shared_ptr<TileSprite> tile_sprite(nullptr);
	std::unique_ptr<sf::Image> tiles(nullptr);
	std::shared_ptr<TextureSkin> skin(nullptr);

	int ac_index;
	int ac_x, ac_y;
	int i, j;

	/* Obrazki bloków. */
	tiles = std::make_unique<sf::Image>();
	if (!tiles->loadFromFile("rc/blocks.png")) {
		throw std::runtime_error(
				"Loading resources "
				"failure.");
	}

	ac_x = (int) (scroll_x - screen_x/2);
	ac_y = (int) (scroll_y - screen_y/2);

	ac_index = 0;
	for (i = 0; i < (int) screen_y; i++) {
		for (j = 0; j < (int) screen_x; j++) {
			skin = std::make_shared<TextureSkin>(*tiles, 11, 1);

			tile_sprite = std::make_shared<TileSprite>
						(skin, Rect(0, 0, 1280, 720), BA_NONE);

			tile_sprite->set_position(Rect(0, 0,
						       80, 80));
			tile_sprite->x = ac_x;
			tile_sprite->y = ac_y;
			tile_sprite->index = ac_index;
			tile_sprite->block_id = 0;

			engine->add_sprite(std::static_pointer_cast<Sprite>(tile_sprite));
			tile_sprite->translate(0, 0);

			ac_x++;
			ac_index++;
		}

		ac_x -= screen_x;
		ac_y++;
	}

	/* Label Sprite. */
	label_sprite = std::make_shared<LabelSprite>(10, 10, &position_str);
	engine->add_sprite(std::static_pointer_cast<Sprite>(label_sprite));

	/* Background Sprite. */
	std::unique_ptr<sf::Image> bg_img = std::make_unique<sf::Image>();
	if (!bg_img->loadFromFile("rc/background.png")) {
		throw std::runtime_error(
				"Loading resources "
				"failure.");
	}
	std::shared_ptr<sf::Texture> bg_texture = std::make_shared<sf::Texture>();
	bg_texture->loadFromImage(*bg_img, sf::IntRect(0, 0, 1280, 720));
	std::shared_ptr<TextureSkin> bg_skin = std::make_shared<TextureSkin>(bg_texture);

	std::shared_ptr<Sprite> bg_sprite = std::make_shared<Sprite>
				(std::static_pointer_cast<SpriteSkin>(bg_skin), -1);
	engine->add_sprite(bg_sprite);

	/* Player Sprite. */
	std::unique_ptr<sf::Image> plr_img = std::make_unique<sf::Image>();
	if (!plr_img->loadFromFile("rc/player.png")) {
		throw std::runtime_error(
				"Loading resources "
				"failure.");
	}
	std::shared_ptr<sf::Texture> plr_texture = std::make_shared<sf::Texture>();
	plr_texture->loadFromImage(*plr_img, sf::IntRect(0, 0, 40, 80));
	std::shared_ptr<TextureSkin> plr_skin = std::make_shared<TextureSkin>(plr_texture);
	player_sprite = std::make_shared<Sprite>
				(std::static_pointer_cast<SpriteSkin>(plr_skin), 5);
	engine->add_sprite(player_sprite);
}

std::unique_ptr<Engine> Game::game_init(void)
{
	std::shared_ptr<GameWindow> window(nullptr);
	std::unique_ptr<Engine> engine(nullptr);

	/* Okno gry. */
	window = std::make_shared<GameWindow>();

	window->set_size(1280, 720);
	window->set_title(std::string("Engine test."));
	window->set_state(GW_ACTIVE);

	/* Silink. */
	engine = std::make_unique<Engine>(on_tick, ticks_in_frame);
	engine->bind_window(window);

	map = generate_map(map_width,
			   map_height,
			   2, 3, 2);
	tile_data = load_tile_data();

	/* Utworzenie duszków bloków,
	 * gracza, tła.
	 * Ustawienie stałych. */
	prepare_game(engine);

	return engine;
}

std::unique_ptr<Engine> Game::engine(nullptr);
Map Game::map;
std::unique_ptr<tile_data_t[]> Game::tile_data(nullptr);
double Game::scroll_x = Game::map_width/2;
double Game::scroll_y = Game::map_height*0.1;
double Game::player_x = Game::map_width/2;
double Game::player_y = Game::map_height*0.1;
double Game::sx = 0;
double Game::sy = 0;

void Game::init(void)
{
	try {
		engine = game_init();
	}
	catch (std::exception &e) {
		throw std::runtime_error(
			"Game initialization "
			"failure.");
	}
}

void Game::exec(void)
{
	engine->exec();
}
