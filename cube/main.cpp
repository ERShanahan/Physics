#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <iostream>

#include "cube.h"
#include "defs.h"

int main() {

    sf::RenderWindow window(sf::VideoMode({WINDOW_X, WINDOW_Y}), "Cube Hehe");

    cube cube(sf::Vector2f(WINDOW_X / 2, WINDOW_Y / 2));

    while (window.isOpen()) {
        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            cube.rotX -= 0.05f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            cube.rotX += 0.05f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            cube.rotY -= 0.05f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            cube.rotY += 0.05f;
        }

        cube.updateFaces();

        window.clear();
        cube.draw(window);
        window.display();
    }

    return 0;
}