#include "cube.h"
#include "face.h"
#include <cmath>

// Helper: rotate a vector about the X and Y axes.
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

cube::cube(sf::Vector3f origin, float size)
    : origin(origin), size(size), rotX(0.f), rotY(0.f)
{
    // Define the six axis-aligned normals for the cube’s faces.
    std::vector<sf::Vector3f> normals = {
        sf::Vector3f(1, 0, 0),    // Right
        sf::Vector3f(-1, 0, 0),   // Left
        sf::Vector3f(0, 1, 0),    // Top
        sf::Vector3f(0, -1, 0),   // Bottom
        sf::Vector3f(0, 0, 1),    // Front
        sf::Vector3f(0, 0, -1)    // Back
    };

    std::vector<sf::Color> colors = {
        sf::Color::Red,        // Right face
        sf::Color::Green,      // Left face
        sf::Color::Blue,       // Top face
        sf::Color::Yellow,     // Bottom face
        sf::Color::Cyan,       // Front face
        sf::Color::Magenta     // Back face
    };

    // Create one face for each normal.
    for (size_t i = 0; i < normals.size(); i++) {
        face f(normals[i], origin, size);
        f.shape.setFillColor(colors[i]);
        faces.push_back(f);
    }
}

void cube::updateFaces() {
    // For each face, apply the cube’s rotation to its base normal and base tangents.
    for (auto &f : faces) {
        sf::Vector3f rotatedNormal   = rotateVector(f.baseNormal, rotX, rotY);
        sf::Vector3f rotatedTangent1 = rotateVector(f.baseTangent1, rotX, rotY);
        sf::Vector3f rotatedTangent2 = rotateVector(f.baseTangent2, rotX, rotY);
        f.update(rotatedNormal, rotatedTangent1, rotatedTangent2, origin, size);
    }
}

void cube::draw(sf::RenderWindow &window, sf::Vector3f viewVector) {
    for (auto &f : faces) {
        float dotProduct = f.normal.x * viewVector.x +
                           f.normal.y * viewVector.y +
                           f.normal.z * viewVector.z;
        if(dotProduct > 0){
            f.draw(window);
        }
    }
}
