#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

class Particle{
public:

    Particle();

    Particle(const sf::Vector2f &position,
             const sf::Vector2f &velocity,
             const sf::Vector2f &acceleration,
             float radius,
             const sf::Color &color);

    void update(float dt);
    void draw(sf::RenderWindow &window) const;

    // Getters
    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    sf::Vector2f getAcceleration() const;
    float getRadius() const;
    sf::Color getColor() const;
    sf::CircleShape &getShape() const;
    float getSize() const;

    // Setters
    void setPosition(const sf::Vector2f &position);
    void setVelocity(const sf::Vector2f &velocity);
    void setAcceleration(const sf::Vector2f &acceleration);
    void setRadius(float radius);
    void setColor(const sf::Color &color);
    void setShape(const sf::CircleShape &shape);
    void setSize(float size);

private:
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    sf::Vector2f m_acceleration;
    float m_radius;
    sf::Color m_color;
    sf::CircleShape m_shape;
    float m_size;
};

#endif //PARTICLE_H