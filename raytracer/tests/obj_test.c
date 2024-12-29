#include "../raylib/src/raylib.h"
#include "../raylib/src/raymath.h"
#include <math.h>
#include <stdio.h>
#include "../raylib/src/raylib.h"
#include "../raylib/src/raymath.h"
#include <math.h>
#include <stdio.h>

#include "../raylib/src/raylib.h"
#include "../raylib/src/raymath.h"
#include <math.h>
#include <stdio.h>

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Raylib 3D Model Rendering");

    // Load the triangulated cube model
    Model model = LoadModel("cube_tri.obj");
  /*  if (!IsModelReady(model)) {
        printf("Failed to load model\n");
        CloseWindow();
        return -1;
    }*/

    // Setup camera
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        DrawModel(model, (Vector3){ 0.0f, 0.0f, 0.0f }, 1.0f, RED);
        DrawGrid(10, 1.0f);
        EndMode3D();

        DrawText("Use WASD and mouse to move the camera", 10, 10, 20, BLACK);
        EndDrawing();
    }

    UnloadModel(model);
    CloseWindow();

    return 0;
}
