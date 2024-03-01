#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

namespace object2D {
    Mesh* CreateSquare(
        const std::string& name,
        glm::vec3 leftBottomCorner,
        float length,
        glm::vec3 color,
        bool fill)
    {
        glm::vec3 corner = leftBottomCorner;

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(length, 0, 0), color),
            VertexFormat(corner + glm::vec3(length, length, 0), color),
            VertexFormat(corner + glm::vec3(0, length, 0), color)
        };

        Mesh* square = new Mesh(name);
        std::vector<unsigned int> indices = { 0, 1, 2, 3 };

        if (!fill) {
            square->SetDrawMode(GL_LINE_LOOP);
        }
        else {
            // Draw 2 triangles. Add the remaining 2 indices
            indices.push_back(0);
            indices.push_back(2);
        }

        square->InitFromData(vertices, indices);
        return square;
    }


    Mesh* CreateEquilateralTriangle(const std::string& name, glm::vec3 corner, float sideLength, glm::vec3 color, bool fill)
    {
       
        glm::vec3 point1(0, sideLength, 0);
        //glm::vec3 point2(sideLength * 0.5f, sideLength * sqrt(3) / 2, 0);
        glm::vec3 point2 = corner + glm::vec3(sideLength * 0.5f, sideLength * sqrt(3) / 2, 0);
        std::vector<VertexFormat> vertices = {
            VertexFormat(corner, color),
            VertexFormat(corner + point1, color),
            VertexFormat(corner + point2, color)
        };

        Mesh* triangle = new Mesh(name);
        std::vector<unsigned int> indices = { 0, 1, 2 };

        if (!fill) {
            triangle->SetDrawMode(GL_LINE_LOOP);
        }
        

        triangle->InitFromData(vertices, indices);
        return triangle;
    }



    Mesh* CreateStar(
        const std::string& name,
        glm::vec3 center,
        float outerRadius,
        float innerRadius,
        glm::vec3 color)
    {
        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;

        int numPoints = 5;

        float angleOffset = glm::radians(90.0f);


        float angleIncrement = 360.0f / numPoints;

        for (int i = 0; i < numPoints * 2; ++i) {
            float angle = glm::radians(i * angleIncrement) + angleOffset;
            float radius;
            if (i % 2 == 0) {
                radius = outerRadius;
            }
            else {
                radius = innerRadius;
            }

            glm::vec3 point = center + glm::vec3(radius * cos(angle), radius * sin(angle), 0.0f);
            vertices.push_back(VertexFormat(point, color));
        }

        for (int i = 0; i < numPoints * 2; i += 2) {
            indices.push_back(i);
            indices.push_back((i + 1) % (numPoints * 2));
            indices.push_back((i + 2) % (numPoints * 2));

            indices.push_back((i + 2) % (numPoints * 2));
            indices.push_back((i + 3) % (numPoints * 2));
            indices.push_back(i + 1);
        }

        Mesh* starMesh = new Mesh(name);
        starMesh->InitFromData(vertices, indices);
        return starMesh;
    }

    Mesh* CreateRhombus(
        const std::string& name,
        glm::vec3 center,
        float sideLength,
        glm::vec3 color)
    {
        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;

        float width = sideLength;
        float height = sideLength / 4;


        glm::vec3 topVertex = center + glm::vec3(0.0f, sideLength, 0.0f);
        glm::vec3 bottomVertex = center - glm::vec3(0.0f, sideLength, 0.0f);
        glm::vec3 leftVertex = center - glm::vec3(sideLength / 2, 0.0f, 0.0f);
        glm::vec3 rightVertex = center + glm::vec3(sideLength / 2, 0.0f, 0.0f);
     
        glm::vec3 topRightCorner = center + glm::vec3(sideLength, height, 0.0f);
        glm::vec3 bottomRightCorner = center - glm::vec3(0.0f, height, 0.0f);
        glm::vec3 topLeftCorner = center + glm::vec3(sideLength, -height, 0.0f);
        glm::vec3 bottomLeftCorner = center - glm::vec3(0.0f, -height, 0.0f);

        vertices.push_back(VertexFormat(topVertex, color));
        vertices.push_back(VertexFormat(leftVertex, color));
        vertices.push_back(VertexFormat(bottomVertex, color));
        vertices.push_back(VertexFormat(rightVertex, color));

        vertices.push_back(VertexFormat(bottomLeftCorner, color));
        vertices.push_back(VertexFormat(bottomRightCorner, color));
        vertices.push_back(VertexFormat(topLeftCorner, color));
        vertices.push_back(VertexFormat(topRightCorner, color));

        indices = { 0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7 };

        Mesh* rhombusMesh = new Mesh(name);
        rhombusMesh->InitFromData(vertices, indices);

        return rhombusMesh;

    }

    Mesh* CreateHexagon(
        const std::string& name,
        glm::vec3 center,
        float sideLength,
        glm::vec3 color)
    {
        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;

        // Define the six vertices of the hexagon
        std::vector<glm::vec3> hexagonVertices;
        for (int i = 0; i < 6; ++i) {
            float angle = i * (2.0f * glm::pi<float>()) / 6.0f;
            glm::vec3 vertex = center + glm::vec3(sideLength * glm::cos(angle), sideLength * glm::sin(angle), 0.0f);
            hexagonVertices.push_back(vertex);
        }

        // Add vertices to the vector
        for (const auto& vertex : hexagonVertices) {
            vertices.push_back(VertexFormat(vertex, color));
        }

        // Add indices to form six triangles
        for (int i = 0; i < 6; ++i) {
            indices.push_back(0);
            indices.push_back(i + 1);
            indices.push_back((i + 1) % 6 + 1);
        }

        // Create and initialize the Mesh
        Mesh* hexagonMesh = new Mesh(name);
        hexagonMesh->InitFromData(vertices, indices);

        return hexagonMesh;
    }

    Mesh* CreateDoubleHexagon(
        const std::string& name,
        glm::vec3 center,
        float bigHexagonSize,
        float smallHexagonSize,
        glm::vec3 colorBig,
        glm::vec3 colorSmall)
    {
        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;
        
        vertices =
        {
            VertexFormat(glm::vec3(-bigHexagonSize/4 * 1.2f, -bigHexagonSize/2, 1), colorBig),
            VertexFormat(glm::vec3(-bigHexagonSize/2 * 1.2f, 0, 1), colorBig),
            VertexFormat(glm::vec3(-bigHexagonSize/4 * 1.2f, bigHexagonSize/2, 1), colorBig),
            VertexFormat(glm::vec3(bigHexagonSize/4 * 1.2f, bigHexagonSize/2, 1), colorBig),
            VertexFormat(glm::vec3(bigHexagonSize / 2 * 1.2f, 0, 1), colorBig),
            VertexFormat(glm::vec3(bigHexagonSize / 4 * 1.2f, -bigHexagonSize / 2, 1), colorBig),

            VertexFormat(glm::vec3(-smallHexagonSize / 4 * 1.2f, -smallHexagonSize / 2, 2), colorSmall),
            VertexFormat(glm::vec3(-smallHexagonSize / 2 * 1.2f, 0, 2), colorSmall),
            VertexFormat(glm::vec3(-smallHexagonSize / 4 * 1.2f, smallHexagonSize / 2, 2), colorSmall),
            VertexFormat(glm::vec3(smallHexagonSize / 4 * 1.2f, smallHexagonSize / 2, 2), colorSmall),
            VertexFormat(glm::vec3(smallHexagonSize / 2 * 1.2f, 0, 2), colorSmall),
            VertexFormat(glm::vec3(smallHexagonSize / 4 * 1.2f, -smallHexagonSize / 2, 2), colorSmall)
        };


        
        indices = { 0, 1, 2, 0, 2, 5, 2, 3, 5, 3, 4, 5, 6, 7, 8, 6, 8, 11, 11, 8, 9, 11, 9, 10};

        Mesh* doubleHexagonMesh = new Mesh(name);
        doubleHexagonMesh->InitFromData(vertices, indices);

        return doubleHexagonMesh;
    }

}
