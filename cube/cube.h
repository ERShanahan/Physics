#ifndef CUBE_H
#define CUBE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "face.h"

class cube {
public:
    sf::Vector2f origin;              // The 2D projection center of the cube.
    std::vector<face> faces;          // The six faces of the cube.
    std::vector<sf::Vector3f> baseNormals; // The original normals (unrotated).

    float size;  // Edge length of the cube.
    float rotX;  // Rotation angle around the X axis (in radians).
    float rotY;  // Rotation angle around the Y axis (in radians).

    cube(sf::Vector2f origin);

    // Apply the current rotation to all base normals and update face geometry.
    void updateFaces();

    void draw(sf::RenderWindow &window);
};

#endif // CUBE_H
