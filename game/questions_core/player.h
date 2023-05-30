#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>
#include <fstream>

#include <json/json.h>
#include <json/value.h>

#include "enemy.h"


class Enemy;
// Class that represents a player - its name, hp and position
class Player
{
    private:

        std::string name;
        int health_points;
        unsigned int pos_x;
        unsigned int pos_y;

    public:

        Player(std::string, int, int, int);
        Player(const Json::Value&);
        std::string get_name() const;
        int get_hp() const;
        unsigned int get_pos_x() const;
        unsigned int get_pos_y() const;

        void set_name(std::string new_name);
        void set_hp(int new_hp);
        void set_pos_x(int new_pos_x);
        void set_pos_y(int new_pos_y);

        unsigned int get_range(Enemy enemy);
        bool is_alive();

        bool operator==(const Player& player) const;
        bool operator!=(const Player& player) const;
        friend std::ostream& operator<<(std::ostream& stream, const Player& player);

	Json::Value dump(void) const;
	void load(const Json::Value&);
};
std::ostream& operator<<(std::ostream& stream, const Player& player);
#endif
