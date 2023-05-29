#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <stdexcept>
#include <iostream>
#include <unistd.h>

#include "menu.h"

void run_game(void)
{
	static char command[] = "bin/game";
	static char *const args[] = {command, nullptr};

	if (execve(command, args, environ) < 0) {
		throw std::runtime_error(
			"Game core app execution "
			"failed.");
	}
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 500), "SFML works!");
    sf::Texture background;

    if(!background.loadFromFile("rc/background.jpg"))
    {
        throw std::invalid_argument("background load error");
    }

    Menu menu(window, background);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    menu.move_up();
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    if (menu.get_text(0).getString() == "Save game")
                    {
                        menu.move_down(1);
                    }
                    else {menu.move_down(0);}
                }
                else if (event.key.code == sf::Keyboard::Return)
                {
                    if (menu.get_pressed_item() == 0)
                    {
                        if (menu.get_text(0).getString() =="Save game")
                        {
                            std::cout << "Save game" << std::endl;
                        }
                        else
                        {
                            window.close();
                            run_game();
                        }
                    }
                    else if (menu.get_pressed_item() == 1)
                    {
                        if (menu.get_text(0).getString() =="Play")
                        {
                            menu.get_text(0).setString("Save game");
                            menu.get_text(0).setFillColor(sf::Color::Blue);
                            menu.get_text(1).setFillColor(sf::Color::Black);
                            menu.get_text(1).setString("Load game from file");
                            menu.get_text(2).setString("");
                            menu.set_index(0);
                        }
                        else
                        {
                            std::cout << "Load game from file" << std::endl;
                        }
                    }
                    else if (menu.get_pressed_item() == 2 && menu.get_text(0).getString() =="Play")
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
