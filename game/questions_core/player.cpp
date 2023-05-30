#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "enemy.h"
#include "player.h"
#include "class_exceptions.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <fstream>


Player::Player(std::string new_name, int new_hp, int new_pos_x, int new_pos_y)
{
    set_name(new_name);
    if (new_hp <=0)
    {
        throw NegativeArgument(new_hp);
    }
    set_hp(new_hp);
    set_pos_x(new_pos_x);
    set_pos_y(new_pos_y);
}

Player::Player(const Json::Value &root) :
name(root["name"].asString()),
health_points(root["hp"].asInt()),
pos_x(root["pos_x"].asInt()),
pos_y(root["pos_y"].asInt())
{
}

std::string Player::get_name() const
{
    return name;
}

int Player::get_hp() const
{
    return health_points;
}

unsigned int Player::get_pos_x() const
{
    return pos_x;
}

unsigned  int Player::get_pos_y() const
{
    return pos_y;
}


void Player::set_name(std::string new_name)
{
    name = new_name;
}

void Player::set_hp(int new_hp)
{
    health_points = new_hp;
}

void Player::set_pos_x(int new_pos_x)
{
    if (new_pos_x < 0)
    {
        throw NegativeArgument(new_pos_x);
    }
    pos_x = new_pos_x;
}

void Player::set_pos_y(int new_pos_y)
{
    if (new_pos_y< 0)
    {
        throw NegativeArgument(new_pos_y);
    }
    pos_y = new_pos_y;
}

unsigned int Player::get_range(Enemy enemy)
{
    int x_diff =  pos_x - enemy.get_pos_x();
    int y_diff = pos_y - enemy.get_pos_y();
    int x_diff_squared = pow((x_diff), 2);
    int y_diff_squared = pow((y_diff), 2);
    return sqrt(x_diff_squared + y_diff_squared);
}

bool Player::is_alive()
{
    if (health_points > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::ostream& operator<<(std::ostream& stream, const Player& player)
{
    stream << player.get_name() << " has " << player.get_hp() << " hp!" << std::endl;
    return stream;
}

bool Player::operator==(const Player& player) const
{
    return name == player.name;
}

bool Player::operator!=(const Player& player) const
{
    return !(*this == player);
}

Json::Value Player::dump(void) const
{
	Json::Value d_root;

	d_root["name"] = this->get_name();
	d_root["hp"] = this->get_hp();
	d_root["pos_x"] = this->get_pos_x();
	d_root["pos_y"] = this->get_pos_y();

	return d_root;
}

void Player::load(const Json::Value &d_root)
{
	set_name(d_root["name"].asString());
	set_hp(d_root["hp"].asInt());
	set_pos_x(d_root["pos_x"].asInt());
	set_pos_y(d_root["pos_y"].asInt());
}
