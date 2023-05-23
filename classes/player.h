// Zoja Hordynska
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>
#include "item.h"
#include "enemy.h"
#include <chrono>
#include <fstream>


class Enemy;
// Class that represents a player - they have a name, hp, strength (for melee weapons), aim (for ranged weapons),
// position, a weapon that they hold and inventory of items
// Items add additional hp, strength or aim
// An item may be added to inventory and removed from it
// Attack damage on an enemy is a random int from a range that gets increased by strength or aim, depending on a type of weapon
class Player
{
    private:

        std::string name;
        int health_points;
        unsigned int pos_x;
        unsigned int pos_y;


    public:

        Player(std::string, int, int, int);
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

        void save_to_file(Player& player, std::string path);
        std::vector<Player> read_from_file(std::string path);
};
std::ostream& operator<<(std::ostream& stream, const Player& player);
#endif
