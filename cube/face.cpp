#include "face.h"
#include <cmath>

// --- Helper functions for vector math ---
static sf::Vector3f cross(const sf::Vector3f &a, const sf::Vector3f &b) {
    return sf::Vector3f(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

static float length(const sf::Vector3f &v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

static sf::Vector3f normalize(const sf::Vector3f &v) {
    float len = length(v);
    return (len == 0.f) ? v : sf::Vector3f(v.x / len, v.y / len, v.z / len);
}

// --- Isometric projection ---
static sf::Vector2f project(const sf::Vector3f &point) {
    float angle = 30.f * 3.14159265f / 180.f;
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);
    float x2d = (point.x - point.z) * cosA;
    float y2d = point.y + (point.x + point.z) * sinA;
    return sf::Vector2f(x2d, y2d);
}

// --- Recalculate the face shape given rotated vectors ---
static void calcShape(sf::ConvexShape &shape,
                        const sf::Vector3f &rotatedNormal,
                        const sf::Vector3f &rotatedTangent1,
                        const sf::Vector3f &rotatedTangent2,
                        const sf::Vector2f &origin,
                        float size)
{
    float half = size / 2.0f;
    // The center of the face (in 3D) is at rotatedNormal * half.
    sf::Vector3f center = rotatedNormal * half;

    // Compute the four corners (maintaining the initial vertex order).
    sf::Vector3f p1 = center - rotatedTangent1 * half - rotatedTangent2 * half;
    sf::Vector3f p2 = center + rotatedTangent1 * half - rotatedTangent2 * half;
    sf::Vector3f p3 = center + rotatedTangent1 * half + rotatedTangent2 * half;
    sf::Vector3f p4 = center - rotatedTangent1 * half + rotatedTangent2 * half;

    shape.setPointCount(4);
    shape.setPoint(0, origin + project(p1));
    shape.setPoint(1, origin + project(p2));
    shape.setPoint(2, origin + project(p3));
    shape.setPoint(3, origin + project(p4));
}

face::face(sf::Vector3f normal, const sf::Vector2f &origin, float size) {
    // Set the base normal.
    baseNormal = normal;
    // Choose a fixed “up” vector; if the normal is vertical, choose another.
    sf::Vector3f up(0, 1, 0);
    if (std::abs(normal.x) < 0.001f && std::abs(normal.z) < 0.001f) {
        up = sf::Vector3f(1, 0, 0);
    }
    // Compute base tangent vectors that determine the face’s intrinsic orientation.
    baseTangent1 = normalize(cross(baseNormal, up));
    baseTangent2 = normalize(cross(baseNormal, baseTangent1));

    // Initially, no rotation has been applied.
    this->normal = baseNormal;

    // Calculate the initial shape.
    calcShape(shape, normal, baseTangent1, baseTangent2, origin, size);
}

void face::update(const sf::Vector3f &rotatedNormal,
                  const sf::Vector3f &rotatedTangent1,
                  const sf::Vector3f &rotatedTangent2,
                  const sf::Vector2f &origin,
                  float size)
{
    normal = rotatedNormal;
    calcShape(shape, rotatedNormal, rotatedTangent1, rotatedTangent2, origin, size);
}

void face::draw(sf::RenderWindow &window) {
    window.draw(shape);
}
