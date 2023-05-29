#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "player.h"
#include "question.h"
#include "enemy.h"
#include "question_ui.h"

TEST_CASE("question_ui tests", "[question_ui]")
{
    Question question1(L"Ile to 2+2?", L"4", L"3", 1);
    Enemy enemy("Bob", 2, 1, 1);
    enemy.set_questions(question1);
    sf::RenderWindow window(sf::VideoMode(1400, 1000), "SFML works!");
    QuestionUI ui(window, enemy);

    CHECK(enemy.number_of_elements() == 1);
    CHECK(ui.get_text(0).getCharacterSize() == 55);
    CHECK(ui.get_text(0).getFillColor() == sf::Color::Black);
    CHECK(ui.get_text(0).getString() == "Ile to 2+2?");
    CHECK(ui.get_text(1).getCharacterSize() == 55);
    CHECK(ui.get_text(1).getFillColor() == sf::Color::Blue);
    CHECK((ui.get_text(1).getString() == "4" ||
	   ui.get_text(1).getString() == "3"));
    CHECK(ui.get_text(2).getCharacterSize() == 55);
    CHECK(ui.get_text(2).getFillColor() == sf::Color::Black);
    CHECK((ui.get_text(2).getString() == "4" ||
	   ui.get_text(2).getString() == "3"));
    CHECK(ui.get_pressed_item() == 1);

    SECTION("change index")
    {
        ui.set_index(1);
        CHECK(ui.get_pressed_item() == 1);
        ui.move_down();
        CHECK(ui.get_pressed_item() == 2);
        ui.move_up();
        CHECK(ui.get_pressed_item() == 1);
    }

    SECTION("exceptions")
    {
        CHECK_THROWS(ui.set_index(4));
        CHECK_THROWS(ui.set_index(-2));
        CHECK_THROWS(ui.answered_correctly(-2));
        CHECK_THROWS(ui.answered_incorrectly(3));
        CHECK_THROWS(ui.answered_incorrectly(-2));
        CHECK_THROWS(ui.answered_incorrectly(3));
    }

    SECTION("correct answer 1")
    {
        ui.answered_correctly(1);
        CHECK(ui.get_text(1).getString() == "Dobrze!");
        CHECK(ui.get_text(0).getString() == "Nacisnij spacje, aby kontynuowac");
    }

    SECTION("correct answer 2")
    {
        ui.answered_correctly(2);
        CHECK(ui.get_text(2).getString() == "Dobrze!");
        CHECK(ui.get_text(0).getString() == "Nacisnij spacje, aby kontynuowac");
    }

    SECTION("incorrect answer 1")
    {
        ui.answered_incorrectly(1);
        CHECK(ui.get_text(1).getString() == "Zle!");
        CHECK(ui.get_text(1).getFillColor() == sf::Color::Red);
        CHECK(ui.get_text(0).getString() == "Nacisnij spacje, aby kontynuowac");
    }

    SECTION("incorrect answer 2")
    {
        ui.answered_incorrectly(2);
        CHECK(ui.get_text(2).getString() == "Zle!");
        CHECK(ui.get_text(2).getFillColor() == sf::Color::Red);
        CHECK(ui.get_text(0).getString() == "Nacisnij spacje, aby kontynuowac");
    }

    SECTION("game over")
    {
        ui.game_over();
        CHECK(ui.get_text(0).getString() == "Nie udalo Ci sie przezyc studiow.");
        CHECK(ui.get_text(0).getFillColor() == sf::Color::Red);
        CHECK(ui.get_text(1).getFillColor() == sf::Color::Black);
        CHECK(ui.get_text(1).getString() == "Nacisnij escape, aby wyjsc");
        CHECK(ui.get_text(2).getString() == "");
    }

    SECTION("reached end")
    {
        ui.reached_end();
        CHECK(ui.get_text(0).getString() == "I tak sie pewnie zobaczymy we wrzesniu...");
        CHECK(ui.get_text(0).getFillColor() == sf::Color::Blue);
        CHECK(ui.get_text(1).getFillColor() == sf::Color::Black);
        CHECK(ui.get_text(1).getString() == "Nacisnij escape, aby wyjsc");
        CHECK(ui.get_text(2).getString() == "");
    }
}
