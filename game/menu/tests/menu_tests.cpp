#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "menu.h"

TEST_CASE("menu tests", "[menu]")
{
    sf::RenderWindow window(sf::VideoMode(1400, 1000), "SFML works!");
    Menu menu(window, sf::Texture());

    CHECK(menu.get_text(0).getCharacterSize() == 80);
    CHECK(menu.get_text(0).getFillColor() == sf::Color::Blue);
    CHECK(menu.get_text(0).getString() == "Play");

    CHECK(menu.get_text(1).getCharacterSize() == 80);
    CHECK(menu.get_text(1).getFillColor() == sf::Color::Black);
    CHECK(menu.get_text(1).getString() == "Options");

    CHECK(menu.get_text(2).getCharacterSize() == 80);
    CHECK(menu.get_text(2).getFillColor() == sf::Color::Black);
    CHECK(menu.get_text(2).getString() == "Exit");

    CHECK(menu.get_pressed_item() == 0);

    SECTION("change index")
    {
        CHECK(menu.get_pressed_item() == 0);
        menu.move_down(0);
        CHECK(menu.get_pressed_item() == 1);
        menu.move_up();
        CHECK(menu.get_pressed_item() == 0);
    }
}
