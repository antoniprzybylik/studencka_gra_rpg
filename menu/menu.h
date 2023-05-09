#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:
    Menu(float width, float height);
    ~Menu();

    void draw(sf::RenderWindow &window);
    void move_up();
    void move_down();
    int get_pressed_item();

private:
    int selected_index;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
    sf::Texture background;
};
