#ifndef FACE_H
#define FACE_H

#include <SFML/Graphics.hpp>
#include <cmath>

class face {
public:
    sf::ConvexShape shape;
    sf::Vector3f normal;

    // Constructor: given a normal vector, the 2D origin (projected cube center), and cube edge length.
    face(sf::Vector3f normal, const sf::Vector2f &origin, float size);

    void update(const sf::Vector3f &rotatedNormal, const sf::Vector2f &origin, float size);

    void draw(sf::RenderWindow &window);
};

#endif // FACE_H
