#pragma once

#include <string>
#include <vector>
#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
   // Mesh* CreateStar(const std::string& name, glm::vec3 center, float outerRadius, float innerRadius, int points, glm::vec3 color);
    Mesh* CreateEquilateralTriangle(const std::string& name, glm::vec3 corner, float sideLength, glm::vec3 color, bool fill);
    Mesh* CreateStar(
        const std::string& name,
        glm::vec3 center,
        float outerRadius,
        float innerRadius,
        glm::vec3 color);

    Mesh* CreateRhombus(
        const std::string& name,
        glm::vec3 center,
        float sideLength,
        glm::vec3 color);

    Mesh* CreateHexagon(
        const std::string& name,
        glm::vec3 center,
        float sideLength,
        glm::vec3 color);

    Mesh* CreateDoubleHexagon(
        const std::string& name,
        glm::vec3 center,
        float bigHexagonSize,
        float smallHexagonSize,
        glm::vec3 colorBig,
        glm::vec3 colorSmall);
}
