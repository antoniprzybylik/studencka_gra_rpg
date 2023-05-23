#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "item.h"
#include "enemy.h"
#include "player.h"
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
        throw std::invalid_argument("Health cannot be of negative value");
    }
    set_hp(new_hp);
    set_pos_x(new_pos_x);
    set_pos_y(new_pos_y);
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
        throw std::invalid_argument("Position cannot be of negative value");
    }
    pos_x = new_pos_x;
}

void Player::set_pos_y(int new_pos_y)
{
    if (new_pos_y< 0)
    {
        throw std::invalid_argument("Position cannot be of negative value");
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

void Player::save_to_file(Player& player, std::string path)
{
    std::ofstream file;
    Player player_to_write(player);
    file.open(path, std::ios::out | std::ios::app);
    if (!file)
    {
        throw std::invalid_argument("Path doesn't exist");
    }
    file<<player_to_write.get_name()<< " "<<player_to_write.get_hp()<<" "<<player_to_write.get_pos_x()<< " " << player_to_write.get_pos_y()<<std::endl;
    file.close();
}

std::vector<Player> Player::read_from_file(std::string path)
{
    std::ifstream file;
    file.open(path);
    if (!file)
    {
        throw std::invalid_argument("Path doesn't exist");
    }
    std::vector<Player> players;
    Player temp(" ", 1, 1, 1);
    while (file >> temp.name >> temp.health_points >> temp.pos_x >> temp.pos_y)
    {
        players.push_back(temp);
    }
    return players;
}
