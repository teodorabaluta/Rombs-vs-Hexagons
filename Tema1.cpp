#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <cmath>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


struct Star {
    float x, y; 
    float appearTime;
    float radius;
};

std::vector<Star> stars;

struct Rhombus {
    float x, y;      
    int color; 
    int render;
    int star_use;
};

std::vector<Rhombus> rhombusObjects;
int onClick = 0;

struct Placed {
    float x, y;
};
std::vector<Placed> placedObj;

Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide1 = 100;
    float squareSide2 = 50;
    const float pi = static_cast<float>(M_PI);
    // compute coordinates of square center
    float cx = corner.x + squareSide1 / 2;
    float cy = corner.y + squareSide1 / 2;


    // initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // initialize angularStep
    angularStep = 0;


    Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide1, glm::vec3(0, 1, 0), true);
    AddMeshToList(square1);

    Mesh* square2 = object2D::CreateSquare("square2", corner, squareSide2, glm::vec3(1, 0, 0), true);
    AddMeshToList(square2);

    Mesh* square3 = object2D::CreateSquare("square3", corner, squareSide1, glm::vec3(1, 1, 1), false);
    AddMeshToList(square3);


    glm::vec3 starCenter = glm::vec3(0, 0, 1);
    float outerRadius = 90;
    float innerRadius = 0.5f;
    glm::vec3 starColor = glm::vec3(1, 1, 1);

    Mesh* star = object2D::CreateStar("star", starCenter, outerRadius, innerRadius, starColor);
    AddMeshToList(star); // STEA ALBA

    Mesh* proiectil = object2D::CreateStar("proiectil", starCenter, outerRadius, innerRadius, glm::vec3(1, 0, 1));
    AddMeshToList(proiectil); // STEA roz = proiectil

    Mesh* steluta = object2D::CreateStar("steluta", starCenter, outerRadius, innerRadius, glm::vec3(1, 0, 0));
    AddMeshToList(steluta); // STEA roz = proiectil

    glm::vec3 triangleCorner = glm::vec3(100.0f, 100.0f, 0.0f);
    float triangleSide = 100.0f;
    glm::vec3 triangleColor = glm::vec3(1.0f, 0.0f, 0.0f);

    Mesh* equilateralTriangle = object2D::CreateEquilateralTriangle("equilateralTriangle", triangleCorner, triangleSide, triangleColor, true);
    AddMeshToList(equilateralTriangle);

    Mesh* rhombusMesh_yellow = object2D::CreateRhombus("rhombusMesh_yellow", glm::vec3(0, 0, 5), 40, glm::vec3(1, 1, 0)); //romb galben
    AddMeshToList(rhombusMesh_yellow);
    romburi.push_back(rhombusMesh_yellow);

    Mesh* rhombusMesh_pink = object2D::CreateRhombus("rhombusMesh_pink", glm::vec3(0, 0, 5), 40, glm::vec3(1, 0, 1)); //romb mov
    AddMeshToList(rhombusMesh_pink);
    romburi.push_back(rhombusMesh_pink);

    Mesh* rhombusMesh_blue = object2D::CreateRhombus("rhombusMesh_blue", glm::vec3(0, 0, 5), 40, glm::vec3(0, 1, 1)); //romb albastru
    AddMeshToList(rhombusMesh_blue);
    romburi.push_back(rhombusMesh_blue);

    Mesh* rhombusMesh_darkblue = object2D::CreateRhombus("rhombusMesh_darkblue", glm::vec3(0, 0, 5), 40, glm::vec3(0, 0, 1)); //romb albastru inchis
    AddMeshToList(rhombusMesh_darkblue);
    romburi.push_back(rhombusMesh_darkblue);

    Mesh* hexa = object2D::CreateHexagon("hexa", corner, 100, glm::vec3(0, 0, 1));
    AddMeshToList(hexa);

    Mesh* hexa_darkblue = object2D::CreateDoubleHexagon("hexa_darkblue", corner, 100, 70, glm::vec3(0, 0, 1), glm::vec3(1, 0, 1));
    AddMeshToList(hexa_darkblue); // albastru + rosu
    enemies.push_back(hexa_darkblue);

    Mesh* hexa_blue = object2D::CreateDoubleHexagon("hexa_blue", corner, 100, 70, glm::vec3(0, 1, 1), glm::vec3(1, 0, 0));
    AddMeshToList(hexa_blue); //albastru + roz
    enemies.push_back(hexa_blue);

    Mesh* hexa_pink = object2D::CreateDoubleHexagon("hexa_pink", corner, 100, 70, glm::vec3(1, 0, 1), glm::vec3(0, 0, 1));
    AddMeshToList(hexa_pink); // roz + blue
    enemies.push_back(hexa_pink);

    Mesh* hexa_yellow = object2D::CreateDoubleHexagon("hexa_yellow", corner, 100, 70, glm::vec3(1, 1, 0), glm::vec3(0, 1, 1));
    AddMeshToList(hexa_yellow);
    enemies.push_back(hexa_yellow);

    //inamic = rand() % 4;
    Mesh* proiectil_darkblue = object2D::CreateStar("proiectil_darkblue", starCenter, outerRadius, innerRadius, glm::vec3(0, 0, 1));
    AddMeshToList(proiectil_darkblue);
    proiectile.push_back(proiectil_darkblue);

    Mesh* proiectil_blue = object2D::CreateStar("proiectil_blue", starCenter, outerRadius, innerRadius, glm::vec3(0, 1, 1));
    AddMeshToList(proiectil_blue);
    proiectile.push_back(proiectil_blue);

    Mesh* proiectil_pink = object2D::CreateStar("proiectil_pink", starCenter, outerRadius, innerRadius, glm::vec3(1, 0, 1));
    AddMeshToList(proiectil_pink);
    proiectile.push_back(proiectil_pink);

    Mesh* proiectil_yellow = object2D::CreateStar("proiectil_yellow", starCenter, outerRadius, innerRadius, glm::vec3(1, 1, 0));
    AddMeshToList(proiectil_yellow);
    proiectile.push_back(proiectil_yellow);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    time = time + 5 * deltaTimeSeconds;
    time_star = time_star + 5 * deltaTimeSeconds;
    //creare 9 patrate
    int i, j;
    for (i = 100; i <= 350; i = i + 125) {
        for (j = 100; j <= 350; j = j + 125) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(i, j);
            RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
        }
    }

    //creare patrate albe contur
    j = j + 75;
    for (i = 100; i <= 550; i = i + 150) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(i, j);
        RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

    }


    //creare arme
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(140, 600);
    RenderMesh2D(meshes["rhombusMesh_yellow"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(290, 600);
    RenderMesh2D(meshes["rhombusMesh_pink"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(440, 600);
    RenderMesh2D(meshes["rhombusMesh_blue"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(590, 600);
    RenderMesh2D(meshes["rhombusMesh_darkblue"], shaders["VertexColor"], modelMatrix);

  //creare dreptunghi
    i = 10;
    for (j = 100; j <= 400; j = j + 50) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(i, j);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
    }

    //creare stelute
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(115, 530);
    modelMatrix *= transform2D::Scale(0.2f, 0.2f);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(265, 530);
    modelMatrix *= transform2D::Scale(0.2f, 0.2f);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(300, 530);
    modelMatrix *= transform2D::Scale(0.2f, 0.2f);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(415, 530);
    modelMatrix *= transform2D::Scale(0.2f, 0.2f);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(450, 530);
    modelMatrix *= transform2D::Scale(0.2f, 0.2f);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(565, 530);
    modelMatrix *= transform2D::Scale(0.2f, 0.2f);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(600, 530);
    modelMatrix *= transform2D::Scale(0.2f, 0.2f);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(635, 530);
    modelMatrix *= transform2D::Scale(0.2f, 0.2f);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);


    j = 575;
    for (i = 0; i < star_contor; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(715 + i * 35, j);
        modelMatrix *= transform2D::Scale(0.2f, 0.2f);
        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
    }

     //miscare proiectil
    totalRadians -= deltaTimeSeconds * 2.5;  
    translateX += deltaTimeSeconds * signT * 100;

    if (totalRadians >= 2.0f * pi) {
        totalRadians -= 2.0f * pi;
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(translateX, 530);
    modelMatrix *= transform2D::Rotate(totalRadians);
    modelMatrix *= transform2D::Scale(0.4f, 0.4f);

    RenderMesh2D(meshes["proiectil"], shaders["VertexColor"], modelMatrix);


    //DISPARITIE INAMIC
    signS = -1;
    if (scaleX > 0) {
        scaleX += deltaTimeSeconds * 0.25 * signS;
        scaleY = scaleX;
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(700, 400);
        modelMatrix *= transform2D::Scale(scaleX, scaleY);

        RenderMesh2D(meshes["hexa_blue"], shaders["VertexColor"], modelMatrix);
    }


    //  DISPARITIE ARMA
    signS = -1;
    if (scaleX > 0) {
        scaleX += deltaTimeSeconds * 0.25 * signS;
        scaleY = scaleX;
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(500, 400);
        modelMatrix *= transform2D::Scale(scaleX, scaleY);

        RenderMesh2D(meshes["rhombusMesh_yellow"], shaders["VertexColor"], modelMatrix);
    }

    if (time > 15.0f) {
        line = rand() % 3;
        inamic = rand() % enemies.size();
        if (line == 0) {
            lines.push_back(glm::vec4(1280, 400, inamic, 0));
        }

        if (line == 1) {
            lines.push_back(glm::vec4(1280, 275, inamic, 0));
        }

        if (line == 2) {
            lines.push_back(glm::vec4(1280, 150, inamic, 0));
        }

        time = 0;

    }

    for (int j = 0; j < lives; j++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(700 + j * 75, 600);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
    }
    OK = 0;
    for (int i = 0; i < lines.size(); i++) {
        float miscare = lines[i].x;
        miscare = miscare - deltaTimeSeconds * signT * 100;
        lines[i].x = miscare;
        signS = -1;

        if (miscare > 90) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(miscare, lines[i].y);
            modelMatrix *= transform2D::Scale(0.5f, 0.5f);
            RenderMesh2D(enemies[lines[i].z], shaders["VertexColor"], modelMatrix);
        }
        else {
            if (scaleX > 0) {
                scaleX += deltaTimeSeconds * 0.25 * signS;
                scaleY = scaleX;
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(miscare, lines[i].y);
                modelMatrix *= transform2D::Scale(scaleX, scaleY);
                RenderMesh2D(enemies[lines[i].z], shaders["VertexColor"], modelMatrix);
                
            }
            if (lines[i].w == 0) {
                lives--;
                lines[i].w = 1;
            }
            cout << lines[i].w << endl;

        }
    }

    if (time_star > 5.0f) {
        Star newStar;
        newStar.x = rand() % 1280;
        newStar.y = rand() % 700;
        newStar.appearTime = time_star;
        stars.push_back(newStar);
        time_star = 0;
    }

    for (const auto& star : stars) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(star.x, star.y);
        modelMatrix *= transform2D::Scale(0.4f, 0.4f);
        RenderMesh2D(meshes["steluta"], shaders["VertexColor"], modelMatrix);
    }

    for (const auto& romb : rhombusObjects) {

        modelMatrix = glm::mat3(1);
        if (romb.render == 1) {
            glm::vec2 cursor = window->GetCursorPosition();
            modelMatrix *= transform2D::Translate(cursor.x, 720 - cursor.y);
        }
        else {

            modelMatrix *= transform2D::Translate(romb.x, romb.y);
            glm::vec2 placedobj = glm::vec2(romb.x, romb.y);
            color = romb.color;
        }
        RenderMesh2D(romburi[romb.color - 1], shaders["VertexColor"], modelMatrix);

    }
}

void Tema1::FrameEnd()
{
}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

}

bool Tema1::IsPointInsideStar(int pointX, int pointY, const Star& star)
{
    float distance = glm::distance(glm::vec2(pointX, pointY), glm::vec2(star.x, star.y));
    return distance <= 30;
}

bool Tema1::IsPointInsideSquare(int pointX, int pointY, int squareX, int squareY, int squareSide1)
{
    return (pointX >= squareX && pointX <= squareX + squareSide1 &&
        (720 - pointY) >= squareY && (720 - pointY) <= squareY + squareSide1);
}

void Tema1::AppearRhombus(int OK) {
    if (OK != 0) {
        glm::vec2 cursor = window->GetCursorPosition();
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(cursor.x, 720 - cursor.y);
        //RenderMesh2D(romburi[romb.color], shaders["VertexColor"], modelMatrix);
    }

}

void Tema1::DrawLives(int lives) 
{
    for (int i = 0; i < lives; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(700 + i * 75, 600);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_2) {

        if (mouseX >= 100 && (720 - mouseY) >= 550 && mouseX <= 200 && (720 - mouseY) <= 650) {
            // adaugi elementul intr un vector de structura rhombus
            Rhombus newRhombus;
            newRhombus.x = mouseX;
            newRhombus.y = 720 - mouseY;
            newRhombus.render = 1;
            newRhombus.color = 1;
            newRhombus.star_use = 1;
            rhombusObjects.push_back(newRhombus);
            romb_color = 1;
            onClick = 1;
        }

        if (IsPointInsideSquare(mouseX, mouseY, 250, 550, 100)) {
            Rhombus newRhombus;
            newRhombus.x = mouseX;
            newRhombus.y = 720 - mouseY;
            newRhombus.render = 1;
            newRhombus.color = 2;
            newRhombus.star_use = 2;
            rhombusObjects.push_back(newRhombus);
            romb_color = 2;
            onClick = 1;
        }

        if (IsPointInsideSquare(mouseX, mouseY, 400, 550, 100)) {
            Rhombus newRhombus;
            newRhombus.x = mouseX;
            newRhombus.y = 720 - mouseY;
            newRhombus.render = 1;
            newRhombus.color = 3;
            newRhombus.star_use = 2;
            rhombusObjects.push_back(newRhombus);
            romb_color = 3;
            onClick = 1;

        }

        if (IsPointInsideSquare(mouseX, mouseY, 550, 550, 100)) {
            Rhombus newRhombus;
            newRhombus.x = mouseX;
            newRhombus.y = 720 - mouseY;
            newRhombus.render = 1;
            newRhombus.color = 4;
            newRhombus.star_use = 3;
            rhombusObjects.push_back(newRhombus);
            romb_color = 4;
            onClick = 1;

        }

        for (int i = 0; i < stars.size(); ++i) {
            if (IsPointInsideStar(mouseX, 720 - mouseY, stars[i])) {
                // Erase the star from the vector
                stars.erase(stars.begin() + i);
                star_contor++;
                break; // Exit the loop since we removed the star

            }
        }
        //cout << star_contor << endl;
    }

    //if (button == GLFW_MOUSE_BUTTON_3) {
    //    //cout << "AAAAAH" << endl;
    //    for (int i = 0; i < rhombusObjects.size(); ++i) {
    //        //if (IsPointInsideRhombus(mouseX, 720 - mouseY, rhombusObjects[i])) {
    //            rhombusObjects.erase(rhombusObjects.begin() + i);
    //            break;
    //        //}
    //    }
    //}
}
bool Tema1::IsPointInsideRhombus(float pointX, float pointY, const Rhombus& romb) {
    float localX = pointX - romb.x;
    float localY = pointY - romb.y;

    float rotatedX = localX * cos(-45.0f) - localY * sin(-45.0f);
    float rotatedY = localX * sin(-45.0f) + localY * cos(-45.0f);

    return true;
}
void Tema1::DropRhombus(int x, int y, int release) {

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x, y);
    RenderMesh2D(romburi[release], shaders["VertexColor"], modelMatrix);

}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
        if (button == GLFW_MOUSE_BUTTON_2) {
            int posX = 0;
            int posY = 0;
            int flag = 0;

            if (!rhombusObjects.empty() && onClick == 1) {
                // take element on release
                Rhombus& romb = rhombusObjects.back();
                for (int i = 100; i <= 350; i = i + 125) {
                    for (int j = 100; j <= 350; j = j + 125) {
                        // if we have a square, flag is 1 
                        if (IsPointInsideSquare(mouseX, mouseY, i, j, 100) && star_contor > romb.star_use) {
                            flag = 1;
                            posX = i + 50;
                            posY = j + 50;
                            star_contor = star_contor - romb.star_use;
                        }

                    }
                }

                if (flag == 0) {
                    // Remove the last element
                    rhombusObjects.pop_back();
                }
                else {
                    romb.render = 0;
                    romb.x = posX;
                    romb.y = posY;
                }
                onClick = 0;
            }
        }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}

