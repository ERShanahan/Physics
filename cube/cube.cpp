#include "cube.h"
#include "face.h"

static sf::Vector3f rotateVector(const sf::Vector3f &v, float angleX, float angleY) {
    // Rotate around X axis.
    float cosX = std::cos(angleX);
    float sinX = std::sin(angleX);
    sf::Vector3f vX(v.x, v.y * cosX - v.z * sinX, v.y * sinX + v.z * cosX);

    // Then rotate around Y axis.
    float cosY = std::cos(angleY);
    float sinY = std::sin(angleY);
    sf::Vector3f vY(vX.x * cosY + vX.z * sinY, vX.y, -vX.x * sinY + vX.z * cosY);
    return vY;
}


cube::cube(sf::Vector2f origin)
    : origin(origin), size(100.f), rotX(0.f), rotY(0.f)
{
    // Define the six axis-aligned normals for a cube.
    baseNormals = {
        sf::Vector3f(1, 0, 0),    // Right
        sf::Vector3f(-1, 0, 0),   // Left
        sf::Vector3f(0, 1, 0),    // Top
        sf::Vector3f(0, -1, 0),   // Bottom
        sf::Vector3f(0, 0, 1),    // Front
        sf::Vector3f(0, 0, -1)    // Back
    };

    // Create initial faces using the unrotated normals.
    for (auto n : baseNormals) {
        faces.push_back(face(n, origin, size));
    }
}

void cube::updateFaces() {
    // For each face, rotate the original normal and update its geometry.
    for (size_t i = 0; i < faces.size(); i++) {
        sf::Vector3f rotated = rotateVector(baseNormals[i], rotX, rotY);
        faces[i].update(rotated, origin, size);
    }
}

void cube::draw(sf::RenderWindow &window) {
    // Draw every face.
    for (auto &f : faces) {
        f.draw(window);
    }
}
