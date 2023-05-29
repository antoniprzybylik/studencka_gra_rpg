#include <iostream>
#include <math.h>
#include "enemy.h"
#include "player.h"
#include "class_exceptions.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stdexcept>


Enemy::Enemy(std::string new_name,
	     int new_attack_dmg,
	     int new_pos_x,
	     int new_pos_y)
{
    set_name(new_name);
    set_attack_damage(new_attack_dmg);
    set_pos_x(new_pos_x);
    set_pos_y(new_pos_y);
    done = false;
}

Enemy::Enemy(Json::Value &root) :
name(root["name"].asString()),
attack_damage(root["attack_damage"].asInt()),
pos_x(root["pos_x"].asInt()),
pos_y(root["pos_y"].asInt()),
done(root["is_done"].asBool())
{
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
        throw NegativeArgument(new_attack_dmg);
    }
    attack_damage = new_attack_dmg;
}

void Enemy::set_pos_x(int new_pos_x)
{
    if (new_pos_x < 0)
    {
        throw NegativeArgument(new_pos_x);
    }
    pos_x = new_pos_x;
}

void Enemy::set_pos_y(int new_pos_y)
{
    if (new_pos_y < 0)
    {
        throw NegativeArgument(new_pos_y);
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
        player.set_hp(player.get_hp() - attack_damage);
    }
    else
    {
        throw AlreadyDead(player.get_hp());
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

Json::Value Enemy::dump(void) const
{
	Json::Value d_root;

	d_root["name"] = this->get_name();
	d_root["attack_damage"] = this->get_attack_damage();
	d_root["pos_x"] = this->get_pos_x();
	d_root["pos_y"] = this->get_pos_y();
	d_root["is_done"] = this->is_done();

	return d_root;
}

void Enemy::load(Json::Value &d_root)
{
	set_name(d_root["name"].asString());
	set_attack_damage(d_root["attack_damage"].asInt());
	set_pos_x(d_root["pos_x"].asInt());
	set_pos_y(d_root["pos_y"].asInt());
	set_done(d_root["is_done"].asBool());
}

void Enemy::set_questions(Question& question)
{
    if (is_in_questions(question.get_id()))
    {
        throw AlreadyExists(question.get_id());
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
        throw WrongId(id);
    }
}

std::string Enemy::get_content_fromid(int id)
{
    if (id >= 0 && id < this->number_of_elements())
    {
        return questions[id].get_content();
    }
    else
    {
      throw OutOfRange(id);
    }
}

std::string Enemy::get_ganswer_fromid(int id)
{
    if (id >= 0 && id < this->number_of_elements())
    {
        return questions[id].get_good_answer();
    }
    else
    {
      throw OutOfRange(id);
    }
}

std::string Enemy::get_wanswer_fromid(int id)
{
    if (id >= 0 && id < this->number_of_elements())
    {
        return questions[id].get_wrong_answer();
    }
    else
    {
      throw OutOfRange(id);
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
      throw DoNotExist(question.get_id());
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
