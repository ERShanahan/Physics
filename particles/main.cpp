#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cmath>
#include <vector>

#include "particle.h"

#define WINDOW_X 1200
#define WINDOW_Y 800

#define GRAVITY 100.0f

#define NUM_PARTICLES 1000


int main() {
    // Create a window with a resolution of 800x600 using an initializer list for sf::Vector2u.
    sf::RenderWindow window(sf::VideoMode({WINDOW_X, WINDOW_Y}), "Particle Simulation");

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Particle particles[NUM_PARTICLES];

    const sf::Vector2f gravity(0.f, GRAVITY);

    for (int i = 0; i < 1000; ++i) {
        // Random position within the window bounds
        float x = static_cast<float>(std::rand() % WINDOW_X);
        float y = static_cast<float>(std::rand() % WINDOW_Y);
        sf::Vector2f position(x, y);

        // Random velocity components between -100 and 100
        float vx = static_cast<float>((std::rand() % 2) - 1);
        float vy = static_cast<float>((std::rand() % 2) - 1);
        sf::Vector2f velocity(vx, vy);

        // No acceleration for now (set to zero)
        sf::Vector2f acceleration = gravity;

        // Define a radius and a color for each particle
        float radius = 1.f;
        sf::Color color = sf::Color::White;

        Particle new_particle = Particle(position, velocity, acceleration, radius, color);
        particles[i] = new_particle;

    }

    // Clock to measure time between frames
    sf::Clock clock;

    // Main loop
    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Get elapsed time since last frame and restart the clock
        float dt = clock.restart().asSeconds();

        // Update each particle
        for (auto &particle : particles) {
            // Update the particle's position based on its velocity and acceleration
            particle.update(dt);

            // Retrieve the particle's current position, velocity, and radius
            sf::Vector2f pos = particle.getPosition();
            float radius = particle.getRadius();
            sf::Vector2f velocity = particle.getVelocity();

            // Bounce off the left/right window boundaries
            if (pos.x - radius < 0 || pos.x + radius > window.getSize().x)
                velocity.x = -velocity.x;
            // Bounce off the top/bottom window boundaries
            if (pos.y - radius < 0 || pos.y + radius > window.getSize().y)
                velocity.y = -velocity.y * 0.99f;

            // Update the particle's velocity if it was modified
            particle.setVelocity(velocity);
        }

        // Check for collisions between particles
        for (size_t i = 0; i < NUM_PARTICLES; ++i) {
            for (size_t j = i + 1; j < NUM_PARTICLES; ++j) {
                sf::Vector2f pos1 = particles[i].getPosition();
                sf::Vector2f pos2 = particles[j].getPosition();
                float r1 = particles[i].getRadius();
                float r2 = particles[j].getRadius();
                sf::Vector2f delta = pos2 - pos1;
                float dist2 = delta.x * delta.x + delta.y * delta.y;
                float radiusSum = r1 + r2;

                if (dist2 < radiusSum * radiusSum) {
                    float distance = std::sqrt(dist2);
                    // Avoid division by zero if particles are exactly at the same position.
                    if (distance == 0.f) {
                        distance = 0.1f;
                        delta = sf::Vector2f(radiusSum, 0.f);
                    }
                    sf::Vector2f normal = delta / distance;

                    // Compute relative velocity along the normal
                    sf::Vector2f v1 = particles[i].getVelocity();
                    sf::Vector2f v2 = particles[j].getVelocity();
                    float relVel = (v1.x - v2.x) * normal.x + (v1.y - v2.y) * normal.y;

                    // For equal masses, the new velocities after an elastic collision are:
                    // v1' = v1 - (relVel * normal)
                    // v2' = v2 + (relVel * normal)
                    sf::Vector2f impulse = normal * relVel;
                    particles[i].setVelocity(v1 - impulse);
                    particles[j].setVelocity(v2 + impulse);
                }
            }
        }

        window.clear();
        for (auto particle: particles){
            particle.draw(window);
        }
        window.display();
        
    }

    return 0;
}
