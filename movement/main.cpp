#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "cube.h"
#include "defs.h"

sf::Vector3f operator+(const sf::Vector3f &a, const sf::Vector3f &b) {
    return sf::Vector3f(a.x + b.x, a.y + b.y, a.z + b.z);
}
sf::Vector3f operator-(const sf::Vector3f &a, const sf::Vector3f &b) {
    return sf::Vector3f(a.x - b.x, a.y - b.y, a.z - b.z);
}
sf::Vector3f operator*(const sf::Vector3f &v, float s) {
    return sf::Vector3f(v.x * s, v.y * s, v.z * s);
}

int main(){

    sf::RenderWindow window(sf::VideoMode({WINDOW_X, WINDOW_Y}), "Cube Hehe");

    cube cube(sf::Vector3f( WINDOW_X / 2, WINDOW_Y / 2, 1), CUBE_SIZE);

    sf::Vector2i prev_mousePixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f prev_mousePos = window.mapPixelToCoords(prev_mousePixelPos);

    sf::Vector3f viewVector(0, 0, 0);
    sf::Vector3f cameraPosition(0, 0, 0);

    while (window.isOpen()) {
        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        sf::Vector2i curr_mousePixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f curr_mousePos = window.mapPixelToCoords(curr_mousePixelPos);
        float dx = curr_mousePos.x - prev_mousePos.x;
        float dy = curr_mousePos.y - prev_mousePos.y;
        // Invert mouse movement to shift the cube’s origin in the opposite direction.
        cube.origin.x += -dx;
        cube.origin.y += -dy;

        float moveSpeed = 0.05f;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
            cameraPosition.y -= moveSpeed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
            cameraPosition.y += moveSpeed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
            cameraPosition.x -= moveSpeed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
            cameraPosition.x += moveSpeed;
        }

        sf::Vector3f viewVector = cube.origin - cameraPosition;
        float mag = std::sqrt(viewVector.x * viewVector.x +
                              viewVector.y * viewVector.y +
                              viewVector.z * viewVector.z);
        if(mag != 0.f) {
            viewVector.x /= mag;
            viewVector.y /= mag;
            viewVector.z /= mag;
        }

        cube.rotX = 0.f;
        cube.rotY = 0.f;
        
        cube.updateFaces();
        
        prev_mousePos = curr_mousePos;
        prev_mousePixelPos = curr_mousePixelPos;

        window.clear();
        cube.draw(window, viewVector);
        window.display();

    }

    return 0;
}