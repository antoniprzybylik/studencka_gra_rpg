#include <iostream>
#include <math.h>
#include "enemy.h"
#include "player.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

const int INIT_DMG_MINI = 1;

Enemy::Enemy(std::string new_name, int new_attack_dmg, int new_pos_x, int new_pos_y)
{
    set_name(new_name);
    set_attack_damage(new_attack_dmg);
    set_pos_x(new_pos_x);
    set_pos_y(new_pos_y);
    done = false;
}

std::string Enemy::get_name() const
{
    return name;
}

unsigned int Enemy::get_attack_damage() const
{
    return attack_damage;
}

unsigned int Enemy::get_pos_x() const
{
    return pos_x;
}

unsigned int Enemy::get_pos_y() const
{
    return pos_y;
}

bool Enemy::is_done() const
{
    return done;
}

void Enemy::set_name(std::string new_name)
{
    name = new_name;
}

void Enemy::set_attack_damage(int new_attack_dmg)
{
    if (new_attack_dmg < 0)
    {
        throw std::invalid_argument("Attack damage cannot be of negative value");
    }
    attack_damage = new_attack_dmg;
}

void Enemy::set_pos_x(int new_pos_x)
{
    if (new_pos_x < 0)
    {
        throw std::invalid_argument("Position cannot be of negative value");
    }
    pos_x = new_pos_x;
}

void Enemy::set_pos_y(int new_pos_y)
{
    if (new_pos_y < 0)
    {
        throw std::invalid_argument("Position cannot be of negative value");
    }
    pos_y = new_pos_y;
}

void Enemy::set_done(bool is_done)
{
    done = is_done;
}

void Enemy::attack(Player &player)
{
    if (player.is_alive())
    {
        srand(time(0));
        player.set_hp(player.get_hp() - (INIT_DMG_MINI + (rand() % attack_damage)));
    }
    else
    {
        throw std::invalid_argument("Player is already dead");
    }
}

std::ostream& operator<<(std::ostream& stream, const Enemy& enemy)
{
    stream << enemy.get_name() << " has " << enemy.get_attack_damage() << " attack damage!" << std::endl;
    return stream;
}

bool Enemy::operator==(const Enemy& enemy) const
{
    return name == enemy.get_name();
}

bool Enemy::operator!=(const Enemy& enemy) const
{
    return !(name == enemy.get_name());
}

Enemy& Enemy::operator=(const Enemy& source)
{
    if(this != &source)
    {
        name = source.name;
        attack_damage = source.attack_damage;
        pos_x = source.pos_x;
        pos_y = source.pos_y;
    }
    return *this;
}

void Enemy::save_to_file(Enemy& enemy, std::string path)
{
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::app);
    if (!file)
    {
        throw std::invalid_argument("Path doesn't exist");
    }
    file<<enemy.get_name()<<" " <<enemy.get_attack_damage()<< " "<<enemy.get_pos_x()<< " "<< std::endl;
    file.close();
}

std::vector<Enemy> Enemy::read_from_file(std::string path)
{
    std::ifstream file;
    file.open(path);
    if (!file)
    {
        throw std::invalid_argument("Path doesn't exist");
    }
    std::vector<Enemy> enemies;
    Enemy temp(" ", 1, 1, 1);
    while (file>>temp.name>>temp.attack_damage>>temp.pos_x>>temp.pos_y)
    {
        enemies.push_back(temp);
    }
    return enemies;
}

void Enemy::set_questions(Question& question)
{
    if (is_in_questions(question.get_id()))
    {
        throw std::invalid_argument("Question already exists");
    }
    questions.push_back(question);
}

bool Enemy::is_in_questions(int id)
{
    auto it = std::find_if(questions.begin(), questions.end(),[&id](const Question& question){return question.get_id() == id;});
    if (it != questions.end())
    {
        return true;
    }
    else
    {
       return false;
    }

}

Question& Enemy::get_question(int id)
{
    if (is_in_questions(id))
    {
        auto it = std::find_if(questions.begin(), questions.end(),[&id](const Question& question){return question.get_id() == id;});
        auto index = std::distance(questions.begin(), it);
        return questions[index];
    }
    else
    {
        throw std::invalid_argument("No such question in an inventory");
    }
}

std::string Enemy::get_content_fromid(int i)
{
    if (i >= 0 && i < this->number_of_elements())
    {
        return questions[i].get_content();
    }
    else
    {
      throw std::invalid_argument("content Out of range");
    }
}

std::string Enemy::get_ganswer_fromid(int i)
{
    if (i >= 0 && i < this->number_of_elements())
    {
        return questions[i].get_good_answear();
    }
    else
    {
      throw std::invalid_argument("ganswer Out of range");
    }
}

std::string Enemy::get_wanswer_fromid(int i)
{
    if (i >= 0 && i < this->number_of_elements())
    {
        return questions[i].get_wrong_answear();
    }
    else
    {
      throw std::invalid_argument("wanser Out of range");
    }
}

void Enemy::remove_question(Question& question)
{
    if (is_in_questions(question.get_id()))
    {
        questions.erase(std::remove(questions.begin(), questions.end(), question));
    }
    else
    {
      throw std::invalid_argument("No such question exists");
    }
}

std::vector<Question> Enemy::get_questions() const
{
    return questions;
}

int Enemy::number_of_elements()
{
    return questions.size();
}