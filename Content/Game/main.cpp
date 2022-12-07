#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include "Point.h"
#include "Map.h"
#include "World.h"


int main()
{

    sf::RenderWindow window(sf::VideoMode(1357, 617), "SFML works!", sf::Style::Close | sf::Style::Titlebar);

    Map map("map.png", "provinces.png");
    World world("provinces.csv");

    sf::View view;

    float zoom = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyPressed:
            {
                switch (event.key.code) {
                case sf::Keyboard::Left:
                    map.moveHorizontaly(100);
                    break;
                case sf::Keyboard::Right:
                    map.moveHorizontaly(-100);
                    break;
                case sf::Keyboard::Up:
                    map.moveVertivaly(100);
                    break;
                case sf::Keyboard::Down:
                    map.moveVertivaly(-100);
                    break;
                }
            }
            case sf::Event::MouseButtonPressed:
            {

                if (event.mouseButton.button == sf::Mouse::Button::Left) {
                    map.select(event.mouseButton.x, event.mouseButton.y);
                    sf::Color color = map.getProvinceColor(event.mouseButton.x, event.mouseButton.y);
                    Province province = world.getProvince(color);
                    std::cout << province.name() << " " << province.color().r << " " << province.color().g << " " << province.color().b << std::endl;
                }
                if (event.mouseButton.button == sf::Mouse::Button::Right) {
                    
                }
            }
            case sf::Event::MouseWheelScrolled:
            {
                //map.addScale(event.mouseWheelScroll.delta);
                zoom -= 0.1;
                view.zoom(zoom);
                window.setView(view);
            }
            default:
                break;
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(map);
        window.display();
    }
    return 0;
}