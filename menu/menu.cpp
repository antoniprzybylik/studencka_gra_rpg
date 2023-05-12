#include "menu.h"
#include <exception>
#include <iostream>
#include <cmath>

Menu::Menu(sf::RenderWindow &window)
{
    if(!background.loadFromFile("background.jpg"))
    {
        throw std::invalid_argument("background load error");
    }

    if(!font.loadFromFile("arial.ttf"))
    {
        throw std::invalid_argument("font load error");
    }

    menu[0].setFont(font);
    menu[0].setCharacterSize(80);
    menu[0].setFillColor(sf::Color::Blue);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(window.getView().getSize().x / 2 - menu[0].getGlobalBounds().width / 2 , window.getView().getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 1));

    menu[1].setFont(font);
    menu[1].setCharacterSize(80);
    menu[1].setFillColor(sf::Color::Black);
    menu[1].setString("Options");
    menu[1].setPosition(sf::Vector2f(window.getView().getSize().x / 2 - menu[1].getGlobalBounds().width / 2, window.getView().getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 2));

    menu[2].setFont(font);
    menu[2].setCharacterSize(80);
    menu[2].setFillColor(sf::Color::Black);
    menu[2].setString("Exit");
    menu[2].setPosition(sf::Vector2f(window.getView().getSize().x / 2 - menu[2].getGlobalBounds().width / 2, window.getView().getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 3));

    selected_index = 0;
}

int Menu::get_pressed_item()
{
    return selected_index;
}

Menu::~Menu()
{
}

void Menu::update_text(sf::RenderWindow &window)
{
    menu[0].setPosition(sf::Vector2f(window.getView().getSize().x / 2 - menu[0].getGlobalBounds().width / 2 , window.getView().getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 1));
    menu[1].setPosition(sf::Vector2f(window.getView().getSize().x / 2 - menu[1].getGlobalBounds().width / 2, window.getView().getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 2));
    menu[2].setPosition(sf::Vector2f(window.getView().getSize().x / 2 - menu[2].getGlobalBounds().width / 2, window.getView().getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 3));
}

void Menu::draw(sf::RenderWindow &window)
{
    sf::Sprite sprite(background);
    sprite.setScale(sf::Vector2f((float)window.getSize().x / (float)sprite.getTexture()->getSize().x, (float)window.getSize().y / (float)sprite.getTexture()->getSize().y));
    window.draw(sprite);
    update_text(window);
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::move_up()
{
    if (selected_index - 1 >= 0)
    {
        menu[selected_index].setFillColor(sf::Color::Black);
        selected_index--;
        menu[selected_index].setFillColor(sf::Color::Blue);
    }
}

void Menu::move_down()
{
    if (selected_index + 1 < MAX_NUMBER_OF_ITEMS)
    {
        menu[selected_index].setFillColor(sf::Color::Black);
        selected_index++;
        menu[selected_index].setFillColor(sf::Color::Blue);
    }
}