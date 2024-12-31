#include "../raylib/src/raylib.h"
#include "../raylib/src/raymath.h"
#include <math.h>
#include <stdio.h>

#define RING_SEGMENTS 64

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "3D Orbital Ring");

    // Initialize camera
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Ring properties
    float ringRadius = 5.0f;
    Color ringColor = SKYBLUE;

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        // Update camera position for rotation
        float time = GetTime();
        camera.position.x = sin(time * 0.5f) * 15.0f;
        camera.position.z = cos(time * 0.5f) * 15.0f;
        camera.position.y = 10.0f;

        BeginDrawing();
            ClearBackground(BLACK);
            
            BeginMode3D(camera);
                // Draw ring segments
                for (int i = 0; i < RING_SEGMENTS; i++) {
                    float angle1 = (2.0f * PI * i) / RING_SEGMENTS;
                    float angle2 = (2.0f * PI * (i + 1)) / RING_SEGMENTS;
                    
                    Vector3 start = {
                        ringRadius * cosf(angle1),
                        0.0f,
                        ringRadius * sinf(angle1)
                    };
                    
                    Vector3 end = {
                        ringRadius * cosf(angle2),
                        0.0f,
                        ringRadius * sinf(angle2)
                    };
                    
                    DrawLine3D(start, end, ringColor);
                }
                // Draw reference grid
                DrawGrid(10, 1.0f);
            EndMode3D();
            
            DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
}
