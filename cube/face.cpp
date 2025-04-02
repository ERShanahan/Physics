#include "face.h"
#include <cmath>

static sf::Vector3f multiply(const sf::Vector3f &v, float s) {
    return sf::Vector3f(v.x * s, v.y * s, v.z * s);
}
static sf::Vector3f add(const sf::Vector3f &a, const sf::Vector3f &b) {
    return sf::Vector3f(a.x + b.x, a.y + b.y, a.z + b.z);
}
static sf::Vector3f subtract(const sf::Vector3f &a, const sf::Vector3f &b) {
    return sf::Vector3f(a.x - b.x, a.y - b.y, a.z - b.z);
}

// Isometric projection function from 3D to 2D.
static sf::Vector2f project(const sf::Vector3f &point) {
    float angle = 30.f * 3.14159265f / 180.f;
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);
    float x2d = (point.x - point.z) * cosA;
    float y2d = point.y + (point.x + point.z) * sinA;
    return sf::Vector2f(x2d, y2d);
}

static void calcShape(sf::ConvexShape &shape, const sf::Vector3f &normal, const sf::Vector2f &origin, float size) {
    float half = size / 2.0f;

    // Determine two tangent vectors based on which axis the normal is primarily aligned with.
    sf::Vector3f tangent1, tangent2;
    if (std::abs(normal.x) > 0.001f) {
        tangent1 = sf::Vector3f(0, 1, 0);
        tangent2 = sf::Vector3f(0, 0, 1);
    } else if (std::abs(normal.y) > 0.001f) {
        tangent1 = sf::Vector3f(1, 0, 0);
        tangent2 = sf::Vector3f(0, 0, 1);
    } else { // normal.z is nonzero
        tangent1 = sf::Vector3f(1, 0, 0);
        tangent2 = sf::Vector3f(0, 1, 0);
    }

    // For a cube centered at the origin, the face center is the normal scaled by half the size.
    sf::Vector3f center = multiply(normal, half);

    // Compute the four corners of the face in 3D.
    sf::Vector3f p1 = subtract(subtract(center, multiply(tangent1, half)), multiply(tangent2, half));
    sf::Vector3f p2 = add(subtract(center, multiply(tangent2, half)), multiply(tangent1, half));
    sf::Vector3f p3 = add(add(center, multiply(tangent1, half)), multiply(tangent2, half));
    sf::Vector3f p4 = subtract(add(center, multiply(tangent2, half)), multiply(tangent1, half));

    // Set up the convex shape using the projected 2D points (offset by the provided origin).
    shape.setPointCount(4);
    shape.setPoint(0, origin + project(p1));
    shape.setPoint(1, origin + project(p2));
    shape.setPoint(2, origin + project(p3));
    shape.setPoint(3, origin + project(p4));
}

face::face(sf::Vector3f normal, const sf::Vector2f &origin, float size)
: normal(normal)
{
    calcShape(shape, normal, origin, size);
}

void face::update(const sf::Vector3f &rotatedNormal, const sf::Vector2f &origin, float size) {
    normal = rotatedNormal;
    calcShape(shape, normal, origin, size);
}

void face::draw(sf::RenderWindow &window) {
    window.draw(shape);
}
