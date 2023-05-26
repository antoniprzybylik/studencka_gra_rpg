#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "menu.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 500), "SFML works!");
    Menu menu(window);


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
                    menu.move_up();
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    menu.move_down();
                }
                else if (event.key.code == sf::Keyboard::Return)
                {
                    if (menu.get_pressed_item() == 0)
                    {
                        std::cout << "Play pressed" << std::endl;
                    }
                    else if (menu.get_pressed_item() == 1)
                    {
                        std::cout << "Options pressed" << std::endl;
                    }
                    else if (menu.get_pressed_item() == 2)
                    {
                        window.close();
                    }
                }
            }
        }

        window.clear();
        window.setView(sf::View(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y)));
        menu.draw(window);
        window.display();
    }

    return 0;
}