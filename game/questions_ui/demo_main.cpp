#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <algorithm>
#include <random>
#include <cstdint>
#include "question_ui.h"
#include "ui_exceptions.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 1000), "SFML works!");

    try
    {
        Player player("Zoja", 3, 1, 1);

        Question question1("Czy zlozyles/as juz legitymacje do podbicia?", "tak", "nie", 1);
        Question question2("Ktorego dnia dziekanat nie przyjmuje studentow?", "sroda", "piatek", 2);
        Question question3("Punkty, przyznawane w ramach zaliczenia przedmiotu to:", "ECTS", "ADTC", 3);

        Question question4("Ktore zdanie jest prawdziwe dla referencji?", "Musi byc zainicjowana.", "Mozna jej przypisac wartosc nullptr.", 4);
        Question question5("Ktory operator mozna przeciazyc? ", "()", "?:", 5);
        Question question6("Rozmiar zmiennej typu int w bajtach to:", "4", "2", 6);

        Question question7("Calka z 5x^4 + 8x to:", "x^5 + 4x^2", " 20x^3 + 8", 7);
        Question question8("Funkcje gestosci rozkladu normalnego opisuje:", "krzywa Gaussa", "funkcja wykladnicza", 8);
        Question question9("Idealne zrodlo napieciowe mozna zastapic:", "zwarciem", "rozwarciem", 9);

        Enemy enemy1("Pani z dziekanatu", 1, 1, 1);
        Enemy enemy2("Prowadzacy", 2, 1, 1);
        Enemy enemy3("Sesja", 3, 1, 1);

        enemy1.set_questions(question1);
        enemy1.set_questions(question2);
        enemy1.set_questions(question3);

        enemy2.set_questions(question4);
        enemy2.set_questions(question5);
        enemy2.set_questions(question6);

        enemy3.set_questions(question7);
        enemy3.set_questions(question8);
        enemy3.set_questions(question9);

        QuestionUI q_ui1(window, enemy1);
        QuestionUI q_ui2(window, enemy2);
        QuestionUI q_ui3(window, enemy3);

        q_ui1.exec(enemy1, player, window);
        //q_ui1.exec(enemy2, player, window);
        //q_ui1.exec(enemy3, player, window);
	
	window.close();

    }
    catch(const LoadError& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(const WrongIndex& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(...)
    {
        std::cerr << "Zlapano inny typ wyjatku" << std::endl;
    }

    return 0;
}
