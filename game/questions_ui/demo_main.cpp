#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <algorithm>
#include <random>
#include <cstdint>

#include <locale>

#include "question_ui.h"
#include "ui_exceptions.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 1000), "SFML works!");
    std::locale::global(std::locale(""));

    try
    {
        Player player("Zoja", 3, 1, 1);

        Question question1(L"Czy masz podbitą legitymację?", L"tak", L"nie", 1);
        Question question2(L"Ktorego dnia dziekanat nie przyjmuje studentow?", L"sroda", L"piatek", 2);
        Question question3(L"Punkty, przyznawane w ramach zaliczenia przedmiotu to:", L"ECTS", L"ADTC", 3);

        Question question4(L"Ktore zdanie jest prawdziwe dla referencji?", L"Musi byc zainicjowana.", L"Mozna jej przypisac wartosc nullptr.", 4);
        Question question5(L"Ktory operator mozna przeciazyc?", L"()", L"?:", 5);
        Question question6(L"Rozmiar zmiennej typu int w bajtach to:", L"4", L"2", 6);

        Question question7(L"Calka z 5x^4 + 8x to:", L"x^5 + 4x^2", L"20x^3 + 8", 7);
        Question question8(L"Funkcje gestosci rozkladu normalnego opisuje:", L"krzywa Gaussa", L"funkcja wykladnicza", 8);
        Question question9(L"Idealne zrodlo napieciowe mozna zastapic:", L"zwarciem", L"rozwarciem", 9);

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

        q_ui1.exec(player);
        //q_ui1.exec(enemy2, player);
        //q_ui1.exec(enemy3, player);
	
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
