#ifndef FACE_H
#define FACE_H

#include <SFML/Graphics.hpp>

class face {
public:
    sf::ConvexShape shape;
    sf::Vector3f baseNormal;
    sf::Vector3f baseTangent1;
    sf::Vector3f baseTangent2;
    sf::Vector3f normal;

    face(sf::Vector3f normal, const sf::Vector2f &origin, float size);

    void update(const sf::Vector3f &rotatedNormal,
                const sf::Vector3f &rotatedTangent1,
                const sf::Vector3f &rotatedTangent2,
                const sf::Vector2f &origin,
                float size);

    void draw(sf::RenderWindow &window);
};

#endif // FACE_H
