#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "question_ui.h"
#include "question.h"
#include "player.h"
#include "enemy.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    Question question("Ile to 2+2?", "3", "4", 1);
    QuestionUI q_ui(window, question.get_content(), question.get_good_answear(), question.get_wrong_answear());
    Player player("Zoja", 10, 1, 1);
    Enemy enemy("Pani z dziekanatu", 2, 1, 1);
    // enemy ma wektor z trzema pytaniami (obiekt Question)
    // okno powinno przechodzic po trzech obiektach, brac z nich pytanie i odpowiedzi, pokazywac na ekran
    // dla kazdego ruchu gracza sprawdzac czy odpowiedz jest poprawna - jesli tak to powinno przejsc do nastepnego
    // jesli nie to zabrac zycie i przejsc do nastepnego
    // sprawdzic czy skonczyly sie obiekty w wektorze - jesli tak to mark enemy jako done (wtedy powinien zniknac z mapy)

    //for dla elementow wektora enemy, tyle ile ich jest
    //pokazanie kazdego z pytan, sprawdzenie odpowiedzi - jesli indeks dobry (albo zly) to i++ i zmienia tekst
    //jak dojdzie do konca to window.close()

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    q_ui.move_up();
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    q_ui.move_down();
                }
                else if (event.key.code == sf::Keyboard::Return)
                {
                    if (q_ui.get_pressed_item() == 1)
                    {
                        if (q_ui.get_text(1).getString() == question.get_good_answear())
                        {
                            q_ui.get_text(1).setString("Correct!");
                        }
                        else
                        {
                            q_ui.get_text(1).setFillColor(sf::Color::Red);
                            q_ui.get_text(1).setString("Wrong!");
                            player.set_hp(player.get_hp() - enemy.get_attack_damage());
                            std::cout << player.get_hp() << std::endl;
                        }

                    }
                    else if (q_ui.get_pressed_item() == 2)
                    {
                        if (q_ui.get_text(2).getString() == question.get_good_answear())
                        {
                            q_ui.get_text(2).setString("Correct!");
                        }
                        else
                        {
                            q_ui.get_text(2).setFillColor(sf::Color::Red);
                            q_ui.get_text(2).setString("Wrong!");
                            player.set_hp(player.get_hp() - enemy.get_attack_damage());
                            std::cout << player.get_hp() << std::endl;
                        }
                    }
                }
            }
        }

        window.clear();
        window.setView(sf::View(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y)));
        q_ui.draw(window);
        window.display();
    }

    return 0;
}