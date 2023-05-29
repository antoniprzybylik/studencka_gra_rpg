#include "question_ui.h"
#include "ui_exceptions.h"
#include <exception>
#include <iostream>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

extern char _binary_font_arial_ttf_start[];
extern char _binary_font_arial_ttf_end[];

extern char _binary_scroll_bgrd_png_start[];
extern char _binary_scroll_bgrd_png_end[];

static std::uniform_int_distribution<unsigned short> pick;
static std::random_device rd;
static std::default_random_engine re(rd());

QuestionUI::QuestionUI(sf::RenderWindow &window, Enemy& new_enemy) :
window(window)
{
    if(!background.loadFromMemory(_binary_scroll_bgrd_png_start,
			          (size_t) ((uint64_t) _binary_scroll_bgrd_png_end -
				            (uint64_t) _binary_scroll_bgrd_png_start)))
    {
        throw LoadError();
    }

    if(!font.loadFromMemory(_binary_font_arial_ttf_start,
			    (size_t) ((uint64_t) _binary_font_arial_ttf_end -
				      (uint64_t) _binary_font_arial_ttf_start)))
    {
        throw LoadError();
    }
    text[0].setFont(font);
    text[0].setCharacterSize(55);
    text[0].setFillColor(sf::Color::Black);
    text[0].setString(new_enemy.get_content_fromid(0));
    text[0].setPosition(sf::Vector2f(window.getView().getSize().x / 2 - text[0].getGlobalBounds().width / 2 , window.getView().getSize().y / (MAX_NUMBER_OF_ITEMS) * 1));

    text[1].setFont(font);
    text[1].setCharacterSize(55);
    text[1].setFillColor(sf::Color::Blue);
    text[1].setPosition(sf::Vector2f(window.getView().getSize().x / 2 - text[1].getGlobalBounds().width / 2, window.getView().getSize().y / (MAX_NUMBER_OF_ITEMS) * 2));

    if ((pick(re) & 1) == 0)
    {
        text[2].setString(new_enemy.get_wanswer_fromid(0));
        text[1].setString(new_enemy.get_ganswer_fromid(0));
    }
    else
    {
        text[1].setString(new_enemy.get_wanswer_fromid(0));
        text[2].setString(new_enemy.get_ganswer_fromid(0));
    }

    text[2].setFont(font);
    text[2].setCharacterSize(55);
    text[2].setFillColor(sf::Color::Black);

    text[2].setPosition(sf::Vector2f(window.getView().getSize().x / 2 - text[2].getGlobalBounds().width / 2, window.getView().getSize().y / (MAX_NUMBER_OF_ITEMS) * 3));

    selected_index = 1;

}

int QuestionUI::get_pressed_item()
{
    return selected_index;
}

void QuestionUI::set_index(int new_index)
{
    if (new_index < MAX_NUMBER_OF_ITEMS && new_index >= 0)
    {
        selected_index = new_index;
    }
    else
    {
        throw WrongIndex(new_index);
    }
}

sf::Text& QuestionUI::get_text(int index)
{
    return text[index];
}

QuestionUI::~QuestionUI()
{
}

void QuestionUI::update_text()
{
    text[0].setPosition(sf::Vector2f(window.getView().getSize().x / 2 - text[0].getGlobalBounds().width / 2 , window.getView().getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 1));
    text[1].setPosition(sf::Vector2f(window.getView().getSize().x / 2 - text[1].getGlobalBounds().width / 2, window.getView().getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 2));
    text[2].setPosition(sf::Vector2f(window.getView().getSize().x / 2 - text[2].getGlobalBounds().width / 2, window.getView().getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 3));
}

void QuestionUI::draw()
{
    sf::Sprite sprite(background);
    sprite.setScale(sf::Vector2f((float)window.getSize().x / (float)sprite.getTexture()->getSize().x, (float)window.getSize().y / (float)sprite.getTexture()->getSize().y));
    window.draw(sprite);
    update_text();
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        window.draw(text[i]);
    }
}

void QuestionUI::move_up()
{
    if (selected_index - 2 >= 0)
    {
        text[selected_index].setFillColor(sf::Color::Black);
        selected_index--;
        text[selected_index].setFillColor(sf::Color::Blue);
    }
}

void QuestionUI::move_down()
{
    if (selected_index + 1 < MAX_NUMBER_OF_ITEMS)
    {
        text[selected_index].setFillColor(sf::Color::Black);
        selected_index++;
        text[selected_index].setFillColor(sf::Color::Blue);
    }
}

void QuestionUI::answered_correctly(int index)
{
    if (index < 0 || index > MAX_NUMBER_OF_ITEMS - 1)
    {
        throw WrongIndex(index);
    }
    else
    {
        text[index].setString("Dobrze!");
        text[0].setString("Nacisnij spacje, aby kontynuowac");
    }
}

void QuestionUI::answered_incorrectly(int index)
{
    if (index < 0 || index > MAX_NUMBER_OF_ITEMS - 1)
    {
        throw WrongIndex(index);
    }
    else
    {
        text[index].setFillColor(sf::Color::Red);
        text[index].setString("Zle!");
        text[0].setString("Nacisnij spacje, aby kontynuowac");
    }
}

void QuestionUI::game_over()
{
    text[0].setString("Nie udalo Ci sie przezyc studiow.");
    text[1].setFillColor(sf::Color::Black);
    text[0].setFillColor(sf::Color::Red);
    text[1].setString("Nacisnij escape, aby wyjsc");
    text[2].setString("");
}

void QuestionUI::reached_end()
{
    text[1].setString("Nacisnij escape, aby wyjsc");
    text[0].setFillColor(sf::Color::Blue);
    text[1].setFillColor(sf::Color::Black);
    text[0].setString("I tak sie pewnie zobaczymy we wrzesniu...");
    text[2].setString("");
}


void QuestionUI::exec(Enemy& enemy, Player& player)
{
    QuestionUI q_ui(window, enemy);
    int i = 0;

    for (;;)
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up && q_ui.get_text(0).getString() == enemy.get_content_fromid(i))
                {
                    q_ui.move_up();
                }
                else if (event.key.code == sf::Keyboard::Down && q_ui.get_text(0).getString() == enemy.get_content_fromid(i))
                {
                    q_ui.move_down();
                }
                else if (event.key.code == sf::Keyboard::Return && q_ui.get_text(0).getString() == enemy.get_content_fromid(i))
                {
                    if (q_ui.get_pressed_item() == 1)
                    {
                        if (q_ui.get_text(1).getString() == enemy.get_ganswer_fromid(i))
                        {
                            q_ui.answered_correctly(1);
                        }
                        else
                        {
                            q_ui.answered_incorrectly(1);
                            enemy.attack(player);
                            if (player.get_hp() <= 0)
                            {
                                q_ui.game_over();
                            }
                        }
                    }
                    else if (q_ui.get_pressed_item() == 2)
                    {
                        if (q_ui.get_text(2).getString() == enemy.get_ganswer_fromid(i))
                        {
                            q_ui.answered_correctly(2);
                        }
                        else
                        {
                            q_ui.answered_incorrectly(2);
                            enemy.attack(player);
                            if (player.get_hp() <= 0)
                            {
                                q_ui.game_over();
                            }
                        }
                    }
                }
                else if (event.key.code == sf::Keyboard::Space && q_ui.get_text(0).getString() == "Nacisnij spacje, aby kontynuowac")
                {
                    if (i == (enemy.number_of_elements() - 1))
                    {
                        q_ui.reached_end();
                        enemy.set_done(true);
                    }
                    else
                    {
                        q_ui.get_text(0).setString(enemy.get_content_fromid(i+1));
                        q_ui.get_text(1).setFillColor(sf::Color::Blue);
                        if ((pick(re) & 1) == 0)
                        {
                            q_ui.get_text(1).setString(enemy.get_ganswer_fromid(i+1));
                            q_ui.get_text(2).setString(enemy.get_wanswer_fromid(i+1));
                        }
                        else
                        {
                            q_ui.get_text(2).setString(enemy.get_ganswer_fromid(i+1));
                            q_ui.get_text(1).setString(enemy.get_wanswer_fromid(i+1));
                        }
                        q_ui.get_text(2).setFillColor(sf::Color::Black);
                        q_ui.set_index(1);
                        i++;
                    }
                }
                else if (event.key.code == sf::Keyboard::Escape && q_ui.get_text(1).getString() == "Nacisnij escape, aby wyjsc")
                {
		    return;
                }
            }
        }
        window.clear();
        window.setView(sf::View(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y)));
        q_ui.draw();
        window.display();
    }
}
