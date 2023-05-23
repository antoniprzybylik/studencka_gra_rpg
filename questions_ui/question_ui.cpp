#include "question_ui.h"
#include <exception>
#include <iostream>
#include <cstdint>
#include <cmath>

extern char _binary_font_arial_ttf_start[];
extern char _binary_font_arial_ttf_end[];

QuestionUI::QuestionUI(sf::RenderWindow &window, std::string question, std::string answer1, std::string answer2)
{
    if(!background.loadFromFile("scroll_bgrd.png"))
    {
        throw std::invalid_argument("background load error");
    }

    if(!font.loadFromMemory(_binary_font_arial_ttf_start,
			    (size_t) ((uint64_t) _binary_font_arial_ttf_end -
				      (uint64_t) _binary_font_arial_ttf_start)))
    {
        throw std::invalid_argument("font load error");
    }

    text[0].setFont(font);
    text[0].setCharacterSize(80);
    text[0].setFillColor(sf::Color::Black);
    text[0].setString(question);
    text[0].setPosition(sf::Vector2f(window.getView().getSize().x / 2 - text[0].getGlobalBounds().width / 2 , window.getView().getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 1));

    text[1].setFont(font);
    text[1].setCharacterSize(80);
    text[1].setFillColor(sf::Color::Blue);
    text[1].setString(answer1);
    text[1].setPosition(sf::Vector2f(window.getView().getSize().x / 2 - text[1].getGlobalBounds().width / 2, window.getView().getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 2));

    text[2].setFont(font);
    text[2].setCharacterSize(80);
    text[2].setFillColor(sf::Color::Black);
    text[2].setString(answer2);
    text[2].setPosition(sf::Vector2f(window.getView().getSize().x / 2 - text[2].getGlobalBounds().width / 2, window.getView().getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 3));

    selected_index = 1;
}

int QuestionUI::get_pressed_item()
{
    return selected_index;
}

sf::Text& QuestionUI::get_text(int index)
{
    return text[index];
}

QuestionUI::~QuestionUI()
{
}

void QuestionUI::update_text(sf::RenderWindow &window)
{
    text[0].setPosition(sf::Vector2f(window.getView().getSize().x / 2 - text[0].getGlobalBounds().width / 2 , window.getView().getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 1));
    text[1].setPosition(sf::Vector2f(window.getView().getSize().x / 2 - text[1].getGlobalBounds().width / 2, window.getView().getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 2));
    text[2].setPosition(sf::Vector2f(window.getView().getSize().x / 2 - text[2].getGlobalBounds().width / 2, window.getView().getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 3));
}

void QuestionUI::draw(sf::RenderWindow &window)
{
    sf::Sprite sprite(background);
    sprite.setScale(sf::Vector2f((float)window.getSize().x / (float)sprite.getTexture()->getSize().x, (float)window.getSize().y / (float)sprite.getTexture()->getSize().y));
    window.draw(sprite);
    update_text(window);
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
