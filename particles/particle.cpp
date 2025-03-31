#include "Particle.h"

// Default constructor
Particle::Particle()
    : m_position(0.f, 0.f),
      m_velocity(0.f, 0.f),
      m_acceleration(0.f, 0.f),
      m_radius(5.f),
      m_color(sf::Color::White),
      m_size(1.f) // Default scale factor
{
    m_shape.setRadius(m_radius);
    m_shape.setFillColor(m_color);
    // Set the origin to the center so that the position corresponds to the center of the circle.
    m_shape.setOrigin(sf::Vector2f(m_radius, m_radius));
    m_shape.setPosition(m_position);
    m_shape.setScale(sf::Vector2f(m_size, m_size));
}

// Parameterized constructor
Particle::Particle(const sf::Vector2f &position,
                   const sf::Vector2f &velocity,
                   const sf::Vector2f &acceleration,
                   float radius,
                   const sf::Color &color)
    : m_position(position),
      m_velocity(velocity),
      m_acceleration(acceleration),
      m_radius(radius),
      m_color(color),
      m_size(1.f) // Default scale factor
{
    m_shape.setRadius(m_radius);
    m_shape.setFillColor(m_color);
    m_shape.setOrigin(sf::Vector2f(m_radius, m_radius));
    m_shape.setPosition(m_position);
    m_shape.setScale(sf::Vector2f(m_size, m_size));
}

// Update particle's state based on elapsed time
void Particle::update(float dt) {
    // Update velocity using acceleration
    m_velocity += m_acceleration * dt;
    // Update position using velocity
    m_position += m_velocity * dt;
    
    // Update the drawable shape's position to match the particle's position
    m_shape.setPosition(m_position);
}

// Draw the particle onto the provided render window
void Particle::draw(sf::RenderWindow &window) const {
    window.draw(m_shape);
}

// Getters
sf::Vector2f Particle::getPosition() const {
    return m_position;
}

sf::Vector2f Particle::getVelocity() const {
    return m_velocity;
}

sf::Vector2f Particle::getAcceleration() const {
    return m_acceleration;
}

float Particle::getRadius() const {
    return m_radius;
}

sf::Color Particle::getColor() const {
    return m_color;
}

// Although declared as const, returning a non-const reference by casting away constness.
// Use with caution.
sf::CircleShape &Particle::getShape() const {
    return const_cast<sf::CircleShape&>(m_shape);
}

float Particle::getSize() const {
    return m_size;
}

// Setters
void Particle::setPosition(const sf::Vector2f &position) {
    m_position = position;
    m_shape.setPosition(m_position);
}

void Particle::setVelocity(const sf::Vector2f &velocity) {
    m_velocity = velocity;
}

void Particle::setAcceleration(const sf::Vector2f &acceleration) {
    m_acceleration = acceleration;
}

void Particle::setRadius(float radius) {
    m_radius = radius;
    m_shape.setRadius(m_radius);
    // Update the origin so the shape remains centered.
    m_shape.setOrigin(sf::Vector2f(m_radius, m_radius));
}

void Particle::setColor(const sf::Color &color) {
    m_color = color;
    m_shape.setFillColor(m_color);
}

void Particle::setShape(const sf::CircleShape &shape) {
    m_shape = shape;
    m_radius = m_shape.getRadius();
    m_color = m_shape.getFillColor();
    m_position = m_shape.getPosition();
}

void Particle::setSize(float size) {
    m_size = size;
    m_shape.setScale(sf::Vector2f(m_size, m_size));
}
