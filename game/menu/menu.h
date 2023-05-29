#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
    private:
        int selected_index;
        sf::Font font;
        sf::Text menu[MAX_NUMBER_OF_ITEMS];
        sf::Texture background;

    public:
        Menu(sf::RenderWindow &window,
	     sf::Texture background);
        ~Menu();

        void draw(sf::RenderWindow &window);
        void update_text(sf::RenderWindow &window);
        void move_up();
        void move_down(int limit);
        int get_pressed_item();
        sf::Text& get_text(int index);
        void set_index(int new_index);
};
