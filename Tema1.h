#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
        struct Star {
            float x, y;        // Position
            float appearTime;  // Time at which the star should appear
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

        struct Placed {
            float x, y;
        };
        std::vector<Placed> placedObj;

     public:
         Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        bool IsPointInsideSquare(int pointX, int pointY, int squareX, int squareY, int squareSide1);
        void AppearRhombus(int OK);
        bool IsPointInsideStar(int pointX, int pointY, const Star& star);
        void DropRhombus(int x, int y, int release);
        void DrawLives(int lives);
        bool IsPointInsideRhombus(float pointX, float pointY, const Rhombus& romb);



     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float angularStep;
        float tx, ty;
        float directiony, theretx, pulse, directionx;
        float squareSide1 = 100;

        float radians, signT = 1, scaleX = 1, scaleY = 1, signS = 1, timeSinceLastAppearance = 0;
        float interval = 2.0f;
        int OK = 0;
        //int AUX;
        int release = 0;
        float totalRadians = 0;
        const float pi = static_cast<float>(M_PI);
        float cellWidth = 100;
        float cellHeight = 100;
        int cellX;
        int cellY;
  
        std::vector<Mesh*> enemies;
        std::vector<glm::vec4> lines; //liniile pe care pot aparea inamicii
        std::vector<Mesh*> romburi;
        std::vector<Mesh*> proiectile;
        glm::vec2 placedobj;

        int line;
        float miscare = 1;
        size_t o;
        int inamic;
        float time = 0;
        int new_o;
        int star_x, star_y;
        float time_star = 0;
        float squareX, squareY;
        float releaseX, releaseY;
        int r_x, r_y;
        int romb_color;
        int star_contor = 8;
        int lives = 3;
        int enemy;
        int color;
    };
}   // namespace m1
