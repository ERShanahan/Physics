#include "Particle.h"
#include <cmath>

Particle::Particle(double* pos_ptr, double* vel_ptr, double* acc_ptr, float radius, const sf::Color& color)
    : pos(pos_ptr), vel(vel_ptr), acc(acc_ptr), radius(radius), color(color)
{
    // Configure the shape with the given radius and color.
    shape.setRadius(radius);
    shape.setFillColor(color);
    // Set the origin to the center.
    shape.setOrigin(sf::Vector2f(radius, radius));
    // Initialize shape's position using the data pointed by pos.
    shape.setPosition(sf::Vector2f(static_cast<float>(pos[0]), static_cast<float>(pos[1])));
}

void Particle::syncShape() {
    // Update the shape's position to reflect the current state in the matrix.
    shape.setPosition(sf::Vector2f(static_cast<float>(pos[0]), static_cast<float>(pos[1])));
}

void Particle::handleBoundaryCollision(const sf::Vector2u& windowSize) {
    // Retrieve current position and velocity.
    float x = static_cast<float>(pos[0]);
    float y = static_cast<float>(pos[1]);
    float vx = static_cast<float>(vel[0]);
    float vy = static_cast<float>(vel[1]);

    // Bounce off left/right boundaries.
    if (x - radius < 0 || x + radius > windowSize.x)
        vx = -vx;
    // Bounce off top/bottom boundaries.
    if (y - radius < 0 || y + radius > windowSize.y)
        vy = -vy * 0.99f;

    // Update the velocity values.
    vel[0] = vx;
    vel[1] = vy;
}

void Particle::draw(sf::RenderWindow &window) {
    window.draw(shape);
}
