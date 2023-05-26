#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <algorithm>
#include <random>
#include <cstdint>
#include "question_ui.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 1000), "SFML works!");
    Question question1("Ile to 2+1?", "3", "4", 1);
    Question question2("Ile to 2+2?", "4", "1", 2);
    Question question3("Ile to 2+3?", "5", "6", 3);
    Enemy enemy("Pani z dziekanatu", 2, 1, 1);
    enemy.set_questions(question1);
    enemy.set_questions(question2);
    enemy.set_questions(question3);
    QuestionUI q_ui(window, enemy);
    Player player("Zoja", 10, 1, 1);

    // enemy ma wektor z trzema pytaniami (obiekt Question)
    // okno przechodzi po trzech obiektach, bierze z nich pytanie i odpowiedzi, pokazuje na ekranie
    // dla kazdego ruchu gracza sprawdza czy odpowiedz jest poprawna - jesli tak to przechodzi do nastepnego
    // jesli nie to zabiera zycie i przechodzi do nastepnego
    // sprawdza czy skonczyly sie obiekty w wektorze - jesli tak to markuje enemy jako done (wtedy powinien zniknac z mapy)

    q_ui.exec(enemy, player, window);
    return 0;
}