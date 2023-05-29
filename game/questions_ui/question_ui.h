#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "question.h"
#include "player.h"
#include "enemy.h"
#define MAX_NUMBER_OF_ITEMS 3
#ifndef QUESTION_UI_H
#define QUESTION_UI_H

class QuestionUI
{
    private:
        int selected_index;
        sf::Font font;
        sf::Text text[MAX_NUMBER_OF_ITEMS];
        sf::Texture background;

	sf::RenderWindow &window;
	Enemy &enemy;

    public:
        QuestionUI(sf::RenderWindow &window, Enemy& new_enemy);
        ~QuestionUI();
        void draw();
        void update_text();
        void move_up();
        void move_down();
        int get_pressed_item();
        void set_index(int new_index);
        sf::Text& get_text(int index);
        void exec(Player& player);
        void answered_correctly(int index);
        void answered_incorrectly(int index);
        void game_over();
        void reached_end();
};

#endif
