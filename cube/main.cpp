#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <iostream>

#include "cube.h"
#include "defs.h"

int main() {

    sf::RenderWindow window(sf::VideoMode({WINDOW_X, WINDOW_Y}), "Cube Hehe");

    cube cube(sf::Vector2f(WINDOW_X / 2, WINDOW_Y / 2), CUBE_SIZE);

    sf::Vector2i prev_mousePixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f prev_mousePos = window.mapPixelToCoords(prev_mousePixelPos);

    while (window.isOpen()) {
        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        sf::Vector2i curr_mousePixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f curr_mousePos = window.mapPixelToCoords(curr_mousePixelPos);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            cube.origin.y -= 0.5f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            cube.origin.y += 0.5f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            cube.origin.x -= 0.5f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            cube.origin.x += 0.5f;
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            float dx = curr_mousePos.x - prev_mousePos.x;
            float dy = curr_mousePos.y - prev_mousePos.y;
            
            cube.rotX += dy * 0.005f;
            cube.rotY -= dx * 0.005f;
        }
        prev_mousePos = curr_mousePos;
        prev_mousePixelPos = curr_mousePixelPos;

        cube.updateFaces();

        window.clear();
        cube.draw(window);
        window.display();
    }

    return 0;
}