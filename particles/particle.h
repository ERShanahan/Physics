#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include "defs.h"


class Particle {
public:
    // Pointers into the simulation matrices.
    // Each pointer should refer to an array of two doubles: [x, y].
    double* pos;
    double* vel;
    double* acc;

    // Particle properties.
    float radius;
    sf::Color color;
    sf::CircleShape shape;

    // Constructor: takes pointers to the particle's row in the matrices.
    Particle(double* pos_ptr, double* vel_ptr, double* acc_ptr, float radius, const sf::Color& color);

    // Sync the drawable shape's position with the particle's state.
    void syncShape();

    // Handle collisions with the window boundaries.
    void handleBoundaryCollision(const sf::Vector2u& windowSize);

    // Draw the particle.
    void draw(sf::RenderWindow &window);
};

#endif // PARTICLE_H
