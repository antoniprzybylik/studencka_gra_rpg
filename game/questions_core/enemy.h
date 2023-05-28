#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>
#include <vector>
#include "player.h"
#include "question.h"

class Question;
class Player;
// Class that represents an enemy with a name, attack damage and position
// contains questions that may be added or removed
class Enemy
{
    private:

        std::string name;
        std::vector <Question> questions;
        unsigned int attack_damage;
        unsigned int pos_x;
        unsigned int pos_y;
        bool done;

    public:

        Enemy(std::string, int, int, int);
        std::string get_name() const;
        unsigned int get_attack_damage() const;
        unsigned int get_pos_x() const;
        unsigned int get_pos_y() const;
        bool is_done() const;

        void set_name(std::string new_name);
        void set_attack_damage(int new_attack_dmg);
        void set_pos_x(int new_pos_x);
        void set_pos_y(int new_pos_y);
        void set_done(bool is_done);

        void attack(Player &player);
        void set_questions(Question& question);
        std::vector<Question> get_questions() const;
        bool is_in_questions(int id);
        Question& get_question(int id);
        std::string get_content_fromid(int id);
        std::string get_ganswer_fromid(int id);
        std::string get_wanswer_fromid(int id);
        void remove_question(Question& question);
        int number_of_elements();

        bool operator==(const Enemy& enemy) const;
        bool operator!=(const Enemy& enemy) const;
        friend std::ostream& operator<<(std::ostream& stream, const Enemy& enemy);
        Enemy& operator=(const Enemy& source);

        void save_to_file(Enemy& enemy, std::string path);
        std::vector<Enemy> read_from_file(std::string path);
};
std::ostream& operator<<(std::ostream& stream, const Enemy& enemy);
#endif
